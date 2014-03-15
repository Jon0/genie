/*
 * State.cpp
 *
 *  Created on: 9/07/2013
 *      Author: asdf
 */

#include <random>

#include "../GenieData/DatFile.h"
#include "../Network/Client.h"
#include "Instance.h"
#include "Player.h"
#include "State.h"

namespace std {

State::State(genie::DatFile *g) {
	gamedata = g;
	edge_length = 0;
	next_id = 0;
	seed = 0;
	client = NULL;
}

State::~State() {

}

void State::startup(int s) {
	cout << "generating map (" << s << ")" << endl;
	seed = s;
	mt19937 gen(seed);

	edge_length = 100;

	/* produce tile array */
	for (int y = 0; y < edge_length; ++y) {
		for (int x = 0; x < edge_length; ++x) {
			tile.push_back(Tile(x, y));
		}
	}

	/* random terrain generation */
	for (int i = 0; i < 50; ++i) {
		int x_pos = gen() % edge_length;
		int y_pos = gen() % edge_length;
		int size = gen() % 50;
		int type = gen() % 18;
		for (int y = y_pos; 0 <= y && y < edge_length && y < y_pos + size;
				++y) {
			for (int x = x_pos;
					0 <= x && x < edge_length && x < x_pos + size; ++x) {
				getTile(x, y)->type = type;
			}
		}
	}

	/* adjacent tile connections */
	for (int y = 0; y < edge_length - 1; ++y) {
		for (int x = 0; x < edge_length - 1; ++x) {
			getTile(x, y)->connect(TILE_NE, getTile(x + 1, y));
			getTile(x, y + 1)->connect(TILE_NW, getTile(x, y));
			getTile(x + 1, y)->connect(TILE_SW, getTile(x, y));
			getTile(x, y)->connect(TILE_SE, getTile(x, y + 1));
		}
	}

	int p1_home_x = 30, p1_home_y = 30, p2_home_x = 70, p2_home_y = 70;

	/* unit types */
	/* unit graphics loading */
	types.reserve(1000);



	/* players with random civ */
	genie::Civ *random_civ = &gamedata->Civs.data()[gen() % gamedata->Civs.size()];
	Player *p1 = new Player(random_civ, gen() % 256, gen() % 256, gen() % 256); // 20, 40, 80
	random_civ = &gamedata->Civs.data()[gen() % gamedata->Civs.size()];
	Player *p2 = new Player(random_civ, gen() % 256, gen() % 256, gen() % 256); // 20, 40, 80

	// nice objects
	int objs[] = { 4, 5, 6, 7, 11,
			24, 37, 38, 39, 40,
			41, 46, 48, 73, 74,
			75, 76, 77, 83, 93,
			94, 122, 123, 216, 218,
			232, 239, 279, 280, 281,
			282, 283, 291, 293, 329,
			358, 359, 441, 448, 474 };

	for (int i = 0; i < 30; ++i) {
		int k = objs[i];

		types.push_back(Type(p1, k));
		Type *random = &types.back();

		for (int i = 0; i < 2; ++i) {
			int x = p1_home_x + (gen() % 50) - 25;
			int y = p1_home_y + (gen() % 50) - 25;
			addObj(Instance(this, random, x, y));
		}

		types.push_back(Type(p2, k));
		random = &types.back();

		for (int i = 0; i < 2; ++i) {
			int x = p2_home_x + (gen() % 50) - 25;
			int y = p2_home_y + (gen() % 50) - 25;
			addObj(Instance(this, random, x, y));
		}

	}

	cout << "completed generating map" << endl;
}

void State::setClient(Client *c) {
	client = c;
}

bool State::withinMap(IsoCoord ic) {
	return 0 <= ic.ne && ic.ne < edge_length && 0 <= ic.se && ic.se < edge_length;
}

void State::update() {
	// update all objects, removing any untasked items
	for (list<Instance>::iterator i = allObj.begin(); i != allObj.end();) {
		if ( (*i).update(this) ) {
			cout << "remove " << &(*i) << endl;

			(*i).on->removeObj(&(*i));
			i = allObj.erase(i);

			cout << "state " << allObj.size() << endl;
		} else {
			++i;
		}
	}
}

void State::addObj(Instance obj) {
	allObj.push_back(obj);
	Instance *ins = &allObj.back();
	getTile(obj.getIso())->addObj(ins);
}

Tile *State::getTile(int x, int y) {
	return &tile.data()[y * edge_length + x];
}

Tile *State::getTile(IsoCoord ic) {
	return getTile(ic.ne, ic.se);
}

Tile *State::getTile(Pointi p) {
	return getTile(p.x, p.y);
}

int State::getMapSize() {
	return edge_length;
}

int State::getNextID() {
	int i = next_id;
	++next_id;
	return i;
}

void State::issueCommand(Instance *a, Instance *b) {
	client->toHost("interact "+to_string(a->state_id)+" "+to_string(b->state_id));
}

void State::issueCommand(Instance *i, IsoCoord ic) {
	client->toHost("move "+to_string(i->state_id)+" "+to_string(ic.ne)+" "+to_string(ic.se));
}

Instance *State::fromID(int id) {
	for (list<Instance>::iterator i = allObj.begin(); i != allObj.end(); ++i) {
		if ( (*i).state_id == id ) {
			return &(*i);
		}
	}



	return NULL;
}

} /* namespace std */
