/*
 * View.cpp
 *
 *  Created on: 7/07/2013
 *      Author: asdf
 */

#include "Model/Player.h"
#include "Model/State.h"
#include "Types/Type.h"
#include "Instance.h"
#include "View.h"

namespace std {

View::View(State *s) {
	Player *p1 = new Player(rand() % 256, rand() % 256, rand() % 256); // 20, 40, 80
	Player *p2 = new Player(rand() % 256, rand() % 256, rand() % 256); // 20, 40, 80

	graph = new DrsFile("resource/graphics.drs");
	terrain = new DrsFile("resource/terrain.drs");
	tile = terrain->getResource(1, false);
	tilen = terrain->getResource(2, false);
	arch = new Type(p1, graph, 0);
	cannon = new Type(p1, graph, 16);
	//knt = new Type(p1, graph, 63);
	knt = new Type(p1, graph, 104);

	state = s;
	new Instance(state, arch, 1, 1);
	new Instance(state, arch, 2, 3);
	select = new Instance(state, knt, 5, 3);

	view_x = 100;
	view_y = 100;

	delete graph;
	delete terrain;
}

void View::scroll(int dx, int dy) {
	view_x += dx;
	view_y += dy;
}

void View::click(int button, int ne, int se) {
	Tile *clicked_tile = state->getTile(ne, se);

	if (0 <= ne && ne < state->getMapSize() && 0 <= se && se < state->getMapSize()) {

		if (button == 0) {
			select = NULL;

			if (clicked_tile->objs() > 0) {
				select = &clicked_tile->getObj()[0];
				cout << "select" << endl;
			}
		}
		else if (button == 2 && select) {
			select->setTask(ne, se, clicked_tile);
		}
	}
}

void View::draw() {
	int draw_view_x = view_x, draw_view_y = view_y;

	for (int se = 0; se < state->getMapSize(); ++se) {
		for (int ne = 0; ne < state->getMapSize(); ++ne) {
			Tile *t = state->getTile(ne, se);

			if ( t->isPassable() ) {
				tile->getFrame(ne+se*10)->draw(draw_view_x+(se+ne)*48, draw_view_y+(ne-se)*24, 48);
			}
			else {
				tilen->getFrame(ne+se*10)->draw(draw_view_x+(se+ne)*48, draw_view_y+(ne-se)*24, 48);
			}

			for (int i = 0; i < t->objs(); ++t) {
				t->getObj()[i].draw(draw_view_x, draw_view_y);
			}
		}
	}
}

void View::test() {
	Ability *a = arch->getAbility(NULL);
	for (int d = 0; d < 8; ++d) {
		for (int t = 0; t < 10; ++t) {
			a->draw((t+1) * 50, (d+1) * 50, d, t);
		}
	}

}

View::~View() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
