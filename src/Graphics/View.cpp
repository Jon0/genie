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
	next_view_x = view_x = 100;
	next_view_y = view_y = 300;
	loaded = false;
	terrain_type = NULL;
	blend = NULL;
	terrain = NULL;
	graph = NULL;
	screen_size = NULL;
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

void View::click(ScreenCoord sc, ScreenCoord down, int button) {
	// calculate isometric coord

	cout << button << endl;
	IsoCoord ic = toIso(sc);
	Tile *clicked_tile = state->getTile(ic.ne, ic.se);

	if (0 <= ic.ne && ic.ne < state->getMapSize() && 0 <= ic.se && ic.se < state->getMapSize()) {

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

			for (int x = lowx; x < highx; ++x) {
				for (int y = lowy; y < highy; ++y) {
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
					//(*i)->setTask(ins);

					state->issueCommand((*i), ins);
				}
				else {
					//(*i)->setTask(new IsoCoord(ic), 0.0f);

					IsoCoord icr;
					icr.ne = ic.ne + (rand() % 2000) / 500.0;
					icr.se = ic.se + (rand() % 2000) / 500.0;
					state->issueCommand((*i), icr);
				}
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

}

void View::debug() {
	for (unordered_set<Instance *>::iterator i = select.begin(); i != select.end(); ++i) {
		cout << "x/y: " << (*i)->current.ne << ", " << (*i)->current.se << endl;
		cout << "tasks " << (*i)->task.size() << endl;
	}
}

void View::loadGraphics() {
	graph = new DrsFile("resource/graphics.drs");
	terrain = new DrsFile("resource/terrain.drs");
	blend = new Blendomatic();

	/* terrain graphics loading */
	terrain_type = new Resource *[18];
	for (int i = 0; i < 18; ++i) {
		terrain_type[i] = terrain->getResource(i, false);
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
		Player *p = t->owner;
		for (int j = 0; j < t->ability.size(); ++j) {
			int gid = t->ability.data()[j]->graphic_id;
			t->ability.data()[j]->assignGraphic( graph->getResource(p, gid, !t->build) );
		}
	}

	delete graph;
	delete terrain;

	loaded = true;
}

} /* namespace std */
