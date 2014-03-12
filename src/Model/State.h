/*
 * State.h
 *
 *  Created on: 9/07/2013
 *      Author: asdf
 */

#ifndef STATE_H_
#define STATE_H_

#include <vector>
#include <list>

#include "../def.h"
#include "Tile.h"
#include "../Types/Type.h"

namespace std {

class Instance;

class State {
public:
	int edge_length, seed;
	vector<Tile> tile;
	vector<Type> types;
	list<Instance> allObj;	// cannot modify sequence

	State();
	virtual ~State();

	void startup(int);
	void update();
	void addObj(Instance);
	Tile *getTile(int, int);
	Tile *getTile(IsoCoord);
	Tile *getTile(Pointi);
	int getMapSize();
};

} /* namespace std */
#endif /* STATE_H_ */
