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
	Player *p1 = new Player(rand() % 256, rand() % 256, rand() % 256); // 20, 40, 80
	Player *p2 = new Player(rand() % 256, rand() % 256, rand() % 256); // 20, 40, 80

	graph = new DrsFile("resource/graphics.drs");
	terrain = new DrsFile("resource/terrain.drs");

	/* terrain graphics loading */
	terrain_type = new Resource *[18];
	for (int i = 0; i < 18; ++i) {
		terrain_type[i] = terrain->getResource(i, false);
	}

	for (int x = 0; x < s->getMapSize(); ++x) {
		for (int y = 0; y < s->getMapSize(); ++y) {
			Tile *t = s->getTile(x, y);
			TileView *tv = new TileView();
			//tiles.push_back(*new TileView());
		}
	}

	arch = new Type(p1, graph, 0);
	cannon = new Type(p1, graph, 16);
	//knt = new Type(p1, graph, 63);
	knt = new Type(p2, graph, 104);

	state = s;
	new Instance(state, arch, 1, 1);
	new Instance(state, arch, 2, 3);
	select = new Instance(state, knt, 5, 3);

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
			select = NULL;

			if (clicked_tile->objs() > 0) {
				select = clicked_tile->getObj(0);
				cout << "select" << endl;
			}
		}
		else if (button == 2 && select) {
			select->setTask(ic.ne, ic.se, clicked_tile);
		}
	}
}

void View::draw() {
	view_x = next_view_x;
	view_y = next_view_y;

	for (int se = 0; se < state->getMapSize(); ++se) {
		for (int ne = 0; ne < state->getMapSize(); ++ne) {
			int tile_x = view_x+(se+ne)*48;
			int tile_y = view_y+(ne-se)*24;

			if (-96 <= tile_x && tile_x < screen_size->x && 0 <= tile_y && tile_y < screen_size->y + 48) {
				Tile *t = state->getTile(ne, se);


				terrain_type[ t->type ]->getFrame(ne+se*10)->draw(tile_x, tile_y, 48);
			/*	if ( t->isPassable() ) {
					terrain_type[0]->getFrame(ne+se*10)->draw(tile_x, tile_y, 48);
				}
				else {
					terrain_type[1]->getFrame(ne+se*10)->draw(tile_x, tile_y, 48);
				}*/

				// draw all objects on the tile
				for (int i = 0; i < t->objs(); ++i) {
					Instance *obj = t->getObj(i);
					ScreenCoord sc = toScreen(obj->getIso());
					obj->draw(sc);

					if (obj == select) {
						obj->type->circle.draw(sc.x, sc.y, 0);
					}
				}
			}
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

	for (int se = 0; se < state->getMapSize(); ++se) {
		cout << ":";
		for (int ne = 0; ne < state->getMapSize(); ++ne) {
			Tile *t = state->getTile(ne, se);
			cout << t->objs() << ", ";
		}
		cout << endl;
	}

}

} /* namespace std */
