/*
 * Path.h
 *
 *  Created on: 26/07/2013
 *      Author: asdf
 */

#ifndef PATH_H_
#define PATH_H_

#include <vector>

#include "../def.h"
#include "Tile.h"

namespace std {

class State;

class Path {
public:
	unsigned short step;
	vector<Tile *> point;	// waypoints
	Path(Tile *, Tile *, float, float);
	Path(State *, IsoCoord, IsoCoord);
	virtual ~Path();
};

} /* namespace std */
#endif /* PATH_H_ */
