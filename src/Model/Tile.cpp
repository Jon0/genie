/*
 * Tile.cpp
 *
 *  Created on: 26/07/2013
 *      Author: remnanjona
 */

#include <stdlib.h>
#include <iostream>
#include "../Instance.h"
#include "Tile.h"

namespace std {

Tile::Tile(unsigned int xi, unsigned int yi, bool p) {
	x = xi;
	y = yi;
	for (int i = 0; i < 4; ++i) {
		adj[i] = NULL;
	}
	pass = p;

}

bool Tile::isPassable() {
	return pass;
}

void Tile::connect(int i, Tile *t) {
	adj[i] = t;
}

Tile *Tile::getAdj(int i) {
	return adj[i];
}

int Tile::objs() {
	return obj.size();
}

Instance *Tile::getObj() {
	return *obj.data();
}

void Tile::addObj(Instance *i) {
	obj.push_back(i);
}

void Tile::removeObj(Instance *ins) {
	for (unsigned int i = 0; i < obj.size(); ++i) {
		//if (obj.data()[i]->x != x && obj.data()[i]->y != y) {
		if (ins == obj.data()[i]) {
			obj.erase(obj.begin() + i);

		}
	}

	//for (vector <Instance *>::iterator iter = obj.begin(); iter != obj.end(); ++iter) {
		//if (ins == obj[iter]) {
		//	obj.erase(iter);
		//}
	//}


	cout << obj.size() << endl;
}

Tile::~Tile() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */