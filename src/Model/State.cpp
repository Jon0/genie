/*
 * State.cpp
 *
 *  Created on: 9/07/2013
 *      Author: asdf
 */

#include "../Types/Move.h"
#include "../Instance.h"
#include "Player.h"
#include "State.h"

namespace std {

State::State() {
	edge_length = 100;

	/* produce tile array */
	for (int y = 0; y < edge_length; ++y) {
		for (int x = 0; x < edge_length; ++x) {
			tile.push_back(Tile(x, y));
		}
	}

	/* random terrain generation */
	for (int i = 0; i < 50; ++i) {
		int x_pos = rand() % edge_length;
		int y_pos = rand() % edge_length;
		int size = rand() % 50;
		int type = rand() % 18;
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
	Player *p1 = new Player(rand() % 256, rand() % 256, rand() % 256); // 20, 40, 80
	Player *p2 = new Player(rand() % 256, rand() % 256, rand() % 256); // 20, 40, 80

	/* unit types */
	/* unit graphics loading */
	types.reserve(1000);
	allObj.reserve(1000);

	for (int i = 0; i < 500; ++i) {
		int k = rand() % 1766;
		types.push_back(Type (p1, k));
		Type *random = &types.back();
		random->addAbility( new Move( k+2, 0.03 ) );
		int x = rand() % getMapSize();
		int y = rand() % getMapSize();
		new Instance(this, random, x, y);
	}



	types.push_back( Type(p1, 0 + 2) );
	Type *arch = &types.back();
	arch->addAbility( new Move( 0+4, 0.03 ) );


	types.push_back(Type (p1, 16 + 2));
	Type *cannon = &types.back();
	cannon->addAbility( new Move( 16+4, 0.02 ) );

	//types.push_back(Type (p1, 63 + 2));
	//Type *arch = &types.back();

	types.push_back(Type (p1, 104 + 2));
	Type *knt = &types.back();
	knt->addAbility( new Move( 104+4, 0.07 ) );

	new Instance(this, arch, 1, 1);
	new Instance(this, arch, 2, 3);
	new Instance(this, cannon, 7, 3);
	new Instance(this, knt, 5, 3);
}

State::~State() {

}

void State::update() {
	for (unsigned int i = 0; i < allObj.size(); ++i) {
		allObj.data()[i]->update();
	}
}

void State::addObj(Instance *obj) {
	allObj.push_back(obj);
	getTile(obj->getIso())->addObj(obj);
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

} /* namespace std */
