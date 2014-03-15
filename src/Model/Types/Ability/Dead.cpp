/*
 * Dead.cpp
 *
 *  Created on: 9/03/2014
 *      Author: remnanjona
 */

#include <iostream>

#include "../../Instance.h"
#include "Dead.h"

namespace std {

Dead::Dead(int gid): Idle(gid) {

}

Dead::~Dead() {
	// TODO Auto-generated destructor stub
}

bool Dead::complete(Instance *i, void *) {
	return (i->dead && i->frame >= group_size-1);
}

bool Dead::update(Instance *i, void *v) {
	i->frame += 0.4f;
	return complete(i, v);
}

} /* namespace std */
