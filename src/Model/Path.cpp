/*
 * Path.cpp
 *
 *  Created on: 26/07/2013
 *      Author: asdf
 */

#include <stdlib.h>
#include <iostream>

#include "State.h"
#include "Path.h"

namespace std {

Path::Path(Tile *start, Tile *end, float x, float y) {
	step = 0;
	//cout << start->x << ", " << start->y << " => "<< end->x << ", " << end->y << " p = " << end->pass << endl;

	Tile *at = start;
	while (at != end) {
		if (at->x < end->x && at->getAdj(0) && at->getAdj(0)->pass) {
			at = at->getAdj(0);
		}
		else if (at->y > end->y && at->getAdj(1) && at->getAdj(1)->pass) {
			at = at->getAdj(1);
		}
		else if (at->x > end->x && at->getAdj(2) && at->getAdj(2)->pass) {
			at = at->getAdj(2);
		}
		else if (at->y < end->y && at->getAdj(3) &&at->getAdj(3)->pass) {
			at = at->getAdj(3);
		}
		else {
			cout << "no path found" << endl;
			break;
		}
		//cout << at->x << ", " << at->y << " => "<< at->pass << endl;

		point.push_back(at);
	}

}

Path::Path(State *s, IsoCoord a, IsoCoord b): Path(
		s->getTile(a.ne, a.se),
		s->getTile(b.ne, b.se),
		a.ne - (int) a.ne,
		b.se - (int) b.se) {

}

Path::~Path() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
