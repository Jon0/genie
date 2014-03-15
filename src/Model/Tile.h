/*
 * Tile.h
 *
 *  Created on: 26/07/2013
 *      Author: remnanjona
 */

#ifndef TILE_H_
#define TILE_H_

#include <vector>

#include "../def.h"

namespace std {

#define TILE_NE 0
#define TILE_NW 1
#define TILE_SW 2
#define TILE_SE 3

class Instance;

class Tile {
	vector<Instance *> obj;
	Tile *adj[4];
	bool pass;

public:
	IsoCoord position;
	unsigned int x, y, type;

	Tile(unsigned int, unsigned int);
	virtual ~Tile();

	bool contains(IsoCoord);
	bool isPassable();
	float dist(IsoCoord);
	void connect(int, Tile *);
	Tile *getAdj(int);
	int objs();
	Instance *getObj(int);
	void addObj(Instance *);
	void removeObj(Instance *i);

};

} /* namespace std */
#endif /* TILE_H_ */
