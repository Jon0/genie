/*
 * State.cpp
 *
 *  Created on: 9/07/2013
 *      Author: asdf
 */

#include <iostream>
#include "../Instance.h"
#include "State.h"

namespace std {

State::State() {
	edge_length = 10;

	/* produce tile array */
	for (int y = 0; y < edge_length; ++y) {
		for (int x = 0; x < edge_length; ++x) {
			tile.push_back(*new Tile(x, y, rand() % 9 != 0));
		}
	}

	/* adjacent tile connections */
	for (int y = 0; y < edge_length - 1; ++y) {
		for (int x = 0; x < edge_length - 1; ++x) {
			getTile(x, y)->connect(0, getTile(x+1, y));
			getTile(x, y+1)->connect(1, getTile(x, y));
			getTile(x+1, y)->connect(2, getTile(x, y));
			getTile(x, y)->connect(3, getTile(x, y+1));
		}
	}
}

void State::update() {
	for (unsigned int i = 0; i < allObj.size(); ++i) {
		allObj.data()[i]->update();
	}
}

void State::addObj(Instance *obj) {
	allObj.push_back(obj);
	getTile( obj->getIso() )->addObj(obj);
}

Tile *State::getTile(int x, int y) {
	return &tile.data()[y * edge_length + x];
}

Tile *State::getTile(IsoCoord ic) {
	int x = ic.ne;
	int y = ic.se;
	return &tile.data()[y * edge_length + x];
}

Tile *State::getTile(Pointi p) {
	return &tile.data()[p.y * edge_length + p.x];
}

int State::getMapSize() {
	return edge_length;
}

State::~State() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
