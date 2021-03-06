/*
 * View.cpp
 *
 *  Created on: 7/07/2013
 *      Author: asdf
 */

#include "../Model/Player.h"
#include "../Model/State.h"
#include "../Model/Types/Type.h"
#include "../Model/Instance.h"
#include "View.h"

namespace std {

View::View(State *s): mm(s) {
	state = s;
	next_view_x = view_x = 100;
	next_view_y = view_y = 300;
	loaded = false;
	terrain_type = NULL;
	blend = NULL;
	terrain = NULL;
	graph = NULL;
	screen_size = NULL;
	select.reserve(100);
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
	//cout << "click " << ic.ne << ", " << ic.se << endl;
	TileView *tv = getTile(ic.ne, ic.se);
	if (tv) return tv->select(this, s);
	return NULL;
}

void View::scroll(int dx, int dy) {
	next_view_x += dx;
	next_view_y += dy;
}

void View::scrollTo(Tile *t) {
	IsoCoord ic;
	ic.ne = t->x;
	ic.se = t->y;

	next_view_x = -(ic.ne + ic.se)*48 + screen_size->x/2;
	next_view_y = -(ic.ne - ic.se - 1)*24 + screen_size->y/2;
}

void View::click(ScreenCoord sc, ScreenCoord down, int button) {
	// calculate isometric coord

	IsoCoord ic = toIso(sc);
	Tile *clicked_tile = state->getTile(ic.ne, ic.se);

	Tile *mmt = mm.onTile(sc);
	if ( mmt ) {
		if (button == 0) scrollTo(mmt);
		else if (button == 1) {
			ic.ne = mmt->x;
			ic.se = mmt->y;
			for (unordered_set<Instance *>::iterator i = select.begin(); i != select.end(); ++i) {
				state->issueCommand((*i), ic);

			}
		}
		return;
	}

	if ( state->withinMap(ic) ) {

		if (button == 0) {

			select.clear();
			int lowx = sc.x, lowy = sc.y, highx = down.x, highy = down.y;
			if (highx < lowx) {
				highx = sc.x;
				lowx = down.x;
			}
			if (highy < lowy) {
				highy = sc.y;
				lowy = down.y;
			}

			for (int x = lowx; x <= highx; ++x) {
				for (int y = lowy; y <= highy; ++y) {
					ScreenCoord sci;
					sci.x = x;
					sci.y = y;

					Instance *test = atPoint(sci);
					if (test) {
						if (select.count(test) == 0) {
							select.insert( test );
							cout << "select " << test->getTask()->graphic_id << endl;
						}
					}
				}
			}


		}

		/* button 2 issues commands to selection */
		else if (button == 1) {
			Instance *ins = atPoint(sc);

			for (unordered_set<Instance *>::iterator i = select.begin(); i != select.end(); ++i) {
				if (ins) {
					state->issueCommand((*i), ins);
				}
				else {
					state->issueCommand((*i), ic);
				}
			}
		}
	}
}

void View::drag(ScreenCoord sc) {
	Tile *mmt = mm.onTile(sc);
	if ( mmt ) {
		scrollTo(mmt);
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

	mm.draw(screen_size);
}

void View::test() {

}

void View::debug() {
	for (unordered_set<Instance *>::iterator i = select.begin(); i != select.end(); ++i) {
		cout << "x/y: " << (*i)->current.ne << ", " << (*i)->current.se << endl;
		cout << "tasks " << (*i)->task.size() << endl;
	}
}

void View::loadGraphics(genie::DatFile *df) {
	graph = new DrsFile("resource/graphics.drs");
	terrain = new DrsFile("resource/terrain.drs");
	blend = new Blendomatic();

	/* terrain graphics loading */
	int color[18];
	terrain_type = new Resource *[18];
	for (int i = 0; i < 18; ++i) {
		terrain_type[i] = terrain->getResource(i);

		color[i] = terrain_type[i]->getFrame(0)->image_data[48 + 97 * 24];
	}

	tiles.clear();
	for (int y = 0; y < state->getMapSize(); ++y) {
		for (int x = 0; x < state->getMapSize(); ++x) {
			Tile *t = state->getTile(x, y);
			tiles.push_back(TileView(t, terrain_type, blend));
		}
	}


	/* unit graphics loading */
	for (int i = 0; i < state->types.size(); ++i) {
		Type *t = &state->types.data()[i];
		Player *p = t->initial_owner;
		for (int j = 0; j < t->ability.size(); ++j) {
			int gid = t->ability.data()[j]->graphic_id;
			genie::Graphic *g = &df->Graphics.data()[gid];
			t->ability.data()[j]->assignGraphic( graph->getSlpFromId(p, g) );
		}
	}

	delete graph;
	delete terrain;

	mm.generate(color);

	loaded = true;
}

} /* namespace std */
