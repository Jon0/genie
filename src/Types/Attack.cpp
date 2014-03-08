/*
 * Attack.cpp
 *
 *  Created on: 8/03/2014
 *      Author: remnanjona
 */

#include "../Resource.h"
#include "../Instance.h"
#include "Attack.h"

namespace std {

Attack::Attack(int gid) {
	graphic_id = gid;
	image = NULL;
	group_size = 0;
}

Attack::~Attack() {
	// TODO Auto-generated destructor stub
}

bool Attack::canInvoke(Instance *i) {
	return i->hp > 0;	// only on positive hp units
}


} /* namespace std */
