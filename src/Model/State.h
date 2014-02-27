/*
 * State.h
 *
 *  Created on: 9/07/2013
 *      Author: asdf
 */

#ifndef STATE_H_
#define STATE_H_

#include <map>
#include "Tile.h"
#include "../def.h"

namespace std {

class Instance;

class State {
	int edge_length;
	vector<Tile> tile;
	vector<Instance *> allObj;
public:
	State();
	void update();
	void addObj(Instance *);
	Tile *getTile(int, int);
	Tile *getTile(IsoCoord ic);
	Tile *getTile(Pointi);
	int getMapSize();
	virtual ~State();
};

} /* namespace std */
#endif /* STATE_H_ */
