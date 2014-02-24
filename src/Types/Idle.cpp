/*
 * Idle.cpp
 *
 *  Created on: 14/07/2013
 *      Author: asdf
 */

#include "../Resource.h"
#include "../Instance.h"
#include "Idle.h"

namespace std {

Idle::Idle(Resource *res) {
	image = res;
	group_size = res->getFrames() / 8;
}

bool Idle::comlpete() {
	return true;
}

void Idle::update(Instance *i) {
	i->frame += 0.3;
}

void Idle::draw(int x, int y, int direction, int tick) {
	image->getFrame(direction * group_size + tick % group_size)->draw(x, y, 0);
}

Idle::~Idle() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
