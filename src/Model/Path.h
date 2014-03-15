/*
 * Path.h
 *
 *  Created on: 26/07/2013
 *      Author: asdf
 */

#ifndef PATH_H_
#define PATH_H_

#include <vector>
#include <queue>

#include "../def.h"
#include "Tile.h"

namespace std {

class State;

struct PathNode {
	Tile *tile;
	float gcost, fcost;
};

struct CostComparator {
  bool operator()(const PathNode& lhs, const PathNode& rhs) const {
    return lhs.fcost > rhs.fcost;
  }
};

class Path {
	queue<Tile *> point;	// waypoints
	IsoCoord *target;
public:
	Path(Tile *, IsoCoord *);
	Path(State *, IsoCoord *, IsoCoord *);
	virtual ~Path();

	int length();
	Tile *next();
	void search(Tile *, IsoCoord *);
};

} /* namespace std */
#endif /* PATH_H_ */
