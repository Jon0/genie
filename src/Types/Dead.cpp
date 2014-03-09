/*
 * Dead.cpp
 *
 *  Created on: 9/03/2014
 *      Author: remnanjona
 */

#include <iostream>

#include "../Instance.h"
#include "Dead.h"

namespace std {

Dead::Dead(int gid): Idle(gid) {

}

Dead::~Dead() {
	// TODO Auto-generated destructor stub
}

bool Dead::update(Instance *i, void *) {
	i->frame += 0.4f;
	return (i->frame >= group_size-1);
}

} /* namespace std */
