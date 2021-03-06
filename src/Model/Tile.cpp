/*
 * Tile.cpp
 *
 *  Created on: 26/07/2013
 *      Author: remnanjona
 */

#include <stdlib.h>
#include <math.h>
#include <iostream>

#include "Instance.h"
#include "Tile.h"

namespace std {

Tile::Tile(unsigned int xi, unsigned int yi) {
	x = xi;
	y = yi;
	for (int i = 0; i < 4; ++i) {
		adj[i] = NULL;
	}
	pass = true;
	type = 0;
	position.ne = xi;
	position.se = yi;
}

Tile::~Tile() {
	// TODO Auto-generated destructor stub
}

bool Tile::contains(IsoCoord ic) {
	return (unsigned int)ic.ne == x && (unsigned int)ic.se == y;
}

bool Tile::isPassable() {
	return obj.size() <= 1;
}

float Tile::dist(IsoCoord point) {
	float dx = point.ne - position.ne;
	float dy = point.se - position.se;
	return sqrt(dx*dx + dy*dy);
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

Instance *Tile::getObj(int i) {
	if (i >= obj.size() ) cout << "tile error: object out of range" <<endl;
	return obj.data()[i];
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


	//cout << obj.size() << endl;
}

} /* namespace std */
