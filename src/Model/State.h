/*
 * State.h
 *
 *  Created on: 9/07/2013
 *      Author: asdf
 */

#ifndef STATE_H_
#define STATE_H_

#include <map>
#include <vector>

#include "../def.h"
#include "Tile.h"
#include "../Types/Type.h"

namespace std {

class Instance;

class State {
public:
	int edge_length;
	vector<Tile> tile;
	vector<Type> types;
	vector<Instance *> allObj;

	State();
	virtual ~State();

	void update();
	void addObj(Instance *);
	Tile *getTile(int, int);
	Tile *getTile(IsoCoord);
	Tile *getTile(Pointi);
	int getMapSize();
};

} /* namespace std */
#endif /* STATE_H_ */
