/*
 * Idle.cpp
 *
 *  Created on: 14/07/2013
 *      Author: asdf
 */

#include "../Instance.h"
#include "Idle.h"

namespace std {

Idle::Idle(int gid) {
	graphic_id = gid;
	image = NULL;
	group_size = 0;
}

void Idle::assignGraphic(Resource *res) {
	image = res;
	group_size = res->getFrames() / 8;
}

bool Idle::comlpete() {
	return true;
}

bool Idle::canInvoke(Instance *) {
	return false;
}

void Idle::update(Instance *i) {
	i->frame += 0.3;
}

void Idle::draw(int x, int y, int direction, int tick) {
	if (group_size == 0) return;

	image->getFrame(direction * group_size + tick % group_size)->draw(x, y, 0);
}

Idle::~Idle() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
