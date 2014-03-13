/*
 * State.cpp
 *
 *  Created on: 9/07/2013
 *      Author: asdf
 */

#include <random>

#include "../Types/Dead.h"
#include "../Types/Idle.h"
#include "../Types/Move.h"
#include "../Types/Attack.h"
#include "../Network/Client.h"
#include "../Instance.h"
#include "Player.h"
#include "State.h"

namespace std {

State::State() {
	edge_length = 0;
	next_id = 0;
	seed = 0;
}

State::~State() {

}

void State::startup(int s) {
	cout << "generating map (" << s << ")" << endl;
	seed = s;
	default_random_engine gen(seed);

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
			getTile(x, y)->connect(0, getTile(x + 1, y));
			getTile(x, y + 1)->connect(1, getTile(x, y));
			getTile(x + 1, y)->connect(2, getTile(x, y));
			getTile(x, y)->connect(3, getTile(x, y + 1));
		}
	}

	/* players */
	Player *p1 = new Player(gen() % 256, gen() % 256, gen() % 256); // 20, 40, 80
	Player *p2 = new Player(gen() % 256, gen() % 256, gen() % 256); // 20, 40, 80

	/* unit types */
	/* unit graphics loading */
	types.reserve(1000);
	//allObj.reserve(1000);


	// nice objects
	int objs[] = {0, 16, 55, 63, 70, 104,
			168, 178, 210, 238, 305,
			354, 453, 491, 496, 693,
			693, 704, 730, 741, 747,
			763, 785, 974, 1278, 1310,
			1334, 1452, 1471, 1480, 1501,
			1759};
	for (int i = 0; i < 32; ++i) {
		int k = objs[i];
		types.push_back(Type (p1, new Dead( k+1 ), false));
		Type *random = &types.back();
		random->addAbility( new Idle( k+2 ) );
		random->addAbility( new Move( k+4, 0.08 ) );
		random->addAbility( new Attack( k ) );

		for (int i = 0; i < 3; ++i) {
			int x = gen() % getMapSize();
			int y = gen() % getMapSize();
			addObj( Instance(this, random, x, y) );
		}
	}

	int blds[] = {575, 1556, 1678};
	for (int i = 0; i < 3; ++i) {
		int k = blds[i];
		types.push_back(Type (p1, new Idle( k ), true));
		Type *random = &types.back();
		for (int i = 0; i < 3; ++i) {
			int x = gen() % getMapSize();
			int y = gen() % getMapSize();
			addObj( Instance(this, random, x, y) );
		}
	}


	types.push_back( Type(p1, new Dead( 0 + 1 ), false) );
	Type *arch = &types.back();
	arch->addAbility( new Idle( 0+2 ) );
	arch->addAbility( new Move( 0+4, 0.08 ) );
	arch->addAbility( new Attack( 0 ) );


	types.push_back(Type (p1, new Dead( 16 + 1 ), false));
	Type *cannon = &types.back();
	cannon->addAbility( new Idle( 16+2 ) );
	cannon->addAbility( new Move( 16+4, 0.06 ) );
	cannon->addAbility( new Attack( 16 ) );

	types.push_back(Type (p1, new Dead( 104 + 1 ), false));
	Type *knt = &types.back();
	knt->addAbility( new Idle( 104+2 ) );
	knt->addAbility( new Move( 104+4, 0.12 ) );
	knt->addAbility( new Attack( 104 ) );

	addObj( Instance(this, arch, 1, 1) );
	addObj( Instance(this, arch, 2, 3) );
	addObj( Instance(this, cannon, 7, 3) );
	addObj( Instance(this, knt, 5, 3) );

	// completly random objects
	for (int i = 0; i < 10; ++i) {
		int k = gen() % 1764;
		types.push_back(Type (p2, new Dead( k+1 ), false));
		Type *random = &types.back();
		random->addAbility( new Idle( k+2 ) );
		random->addAbility( new Move( k+4, 0.08 ) );
		int x = gen() % getMapSize();
		int y = gen() % getMapSize();
		addObj( Instance(this, random, x, y) );
	}

	for (int i = 0; i < 20; ++i) {
		int k = gen() % 1764;
		types.push_back(Type (p2, new Idle( k ), true));
		Type *random = &types.back();

		int x = gen() % getMapSize();
		int y = gen() % getMapSize();
		addObj( Instance(this, random, x, y) );
	}

	cout << "completed generating map" << endl;
}

void State::setClient(Client *c) {
	client = c;
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
