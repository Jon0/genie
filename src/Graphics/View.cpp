/*
 * View.cpp
 *
 *  Created on: 7/07/2013
 *      Author: asdf
 */

#include "../Model/Player.h"
#include "../Model/State.h"
#include "../Types/Type.h"
#include "../Instance.h"
#include "View.h"

namespace std {

View::View(State *s) {
	state = s;

	graph = new DrsFile("resource/graphics.drs");
	terrain = new DrsFile("resource/terrain.drs");
	blend = new Blendomatic();

	/* terrain graphics loading */
	terrain_type = new Resource *[18];
	for (int i = 0; i < 18; ++i) {
		terrain_type[i] = terrain->getResource(i, false);
	}

	for (int y = 0; y < s->getMapSize(); ++y) {
		for (int x = 0; x < s->getMapSize(); ++x) {
			Tile *t = s->getTile(x, y);
			tiles.push_back(TileView(t, terrain_type, blend));
		}
	}

	/* unit graphics loading */
	for (int i = 0; i < s->types.size(); ++i) {
		Type *t = &s->types.data()[i];
		Player *p = t->owner;
		for (int j = 0; j < t->ability.size(); ++j) {
			int gid = t->ability.data()[j]->graphic_id;
			t->ability.data()[j]->assignGraphic( graph->getResource(p, gid, true) );
		}
	}

	next_view_x = 100;
	next_view_y = 300;

	delete graph;
	delete terrain;
}

View::~View() {
	// TODO Auto-generated destructor stub
}

IsoCoord View::toIso(ScreenCoord sc) {
	IsoCoord i;

	float rx = (sc.x - view_x) / 96.0;
	float ry = (sc.y - view_y + 24) / 48.0;
	i.ne = rx + ry;
	i.se = rx - ry;

	return i;
}

ScreenCoord View::toScreen(IsoCoord ic) {
	ScreenCoord s;
	s.x = view_x+(ic.ne + ic.se)*48;
	s.y = view_y+(ic.ne - ic.se - 1)*24;
	return s;
}

void View::size_ref(ScreenCoord *s) {
	screen_size = s;
}

TileView *View::getTile(int x, int y) {
	if (0 <= x && x < state->getMapSize() && 0 <= y && y < state->getMapSize())
		return &tiles.data()[y * state->getMapSize() + x];
	return NULL;
}

Instance *View::atPoint(ScreenCoord s) {
	IsoCoord ic = toIso(s);
	cout << "click " << ic.ne << ", " << ic.se << endl;
	TileView *tv = getTile(ic.ne, ic.se);
	if (tv) return tv->select(this, s);
	return NULL;
}

void View::scroll(int dx, int dy) {
	next_view_x += dx;
	next_view_y += dy;
}

void View::click(ScreenCoord sc, int button) {
	// calculate isometric coord
	IsoCoord ic = toIso(sc);
	Tile *clicked_tile = state->getTile(ic.ne, ic.se);

	if (0 <= ic.ne && ic.ne < state->getMapSize() && 0 <= ic.se && ic.se < state->getMapSize()) {

		if (button == 0) {
			select = atPoint(sc);

			if (select) {
				cout << "select " << select->getTask()->graphic_id << endl;
			}
		}

		/* button 2 issues commands to selection */
		else if (button == 2 && select) {
			Instance *ins = atPoint(sc);
			if (ins) {
				select->setTask(ins);
			}
			else {
				select->setTask(ic.ne, ic.se, clicked_tile);
			}
		}
	}
}

void View::draw() {
	view_x = next_view_x;
	view_y = next_view_y;

	for (int se = 0; se < state->getMapSize(); ++se) {
		for (int ne = 0; ne < state->getMapSize(); ++ne) {
			TileView *vt = getTile(ne, se);
			vt->draw(this);
		}
	}
}

void View::test() {
	Ability *a = knt->getAbility(NULL);
	for (int d = 0; d < 8; ++d) {
		for (int t = 0; t < 10; ++t) {
			a->draw((t+1) * 50, (d+1) * 50, d, t);
		}
	}

}

void View::debug() {
	if (select == NULL) {
		cout << "no selection" << endl;
	}
	else {
		cout << "x/y: " << select->current.ne << ", " << select->current.se << endl;
	}
}

} /* namespace std */
