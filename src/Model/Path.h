/*
 * Path.h
 *
 *  Created on: 26/07/2013
 *      Author: asdf
 */

#ifndef PATH_H_
#define PATH_H_

#include <vector>
#include "Tile.h"

namespace std {

class Path {
public:
	unsigned short step;
	vector<Tile *> point;	// waypoints
	Path(Tile *, Tile *, float, float);
	virtual ~Path();
};

} /* namespace std */
#endif /* PATH_H_ */
