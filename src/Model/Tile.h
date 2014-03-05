/*
 * Tile.h
 *
 *  Created on: 26/07/2013
 *      Author: remnanjona
 */

#ifndef TILE_H_
#define TILE_H_

#include <vector>

namespace std {

class Instance;

class Tile {
	vector<Instance *> obj;
	Tile *adj[4];

public:
	unsigned int x, y, type;
	bool pass;
	Tile(unsigned int, unsigned int);
	bool isPassable();
	void connect(int, Tile *);
	Tile *getAdj(int);
	int objs();
	Instance *getObj(int);
	void addObj(Instance *);
	void removeObj(Instance *i);
	virtual ~Tile();
};

} /* namespace std */
#endif /* TILE_H_ */
