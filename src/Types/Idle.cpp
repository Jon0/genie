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
	inc_rate = 0.3;
}

void Idle::assignGraphic(Resource *res) {
	image = res;

	if ( res->getFrames()  >= 8) {
		group_size = res->getFrames() / 8;
	}
	else {
		group_size = res->getFrames();
		inc_rate = 0.01;
	}
}

bool Idle::comlpete() {
	return true;
}

bool Idle::canInvoke(Instance *i) {
	return i == NULL;
}

bool Idle::canInvoke(IsoCoord *) {
	return false;
}

void Idle::invoke(Instance *i, Instance *) {
	task_arg t;
	t.ability = this;
	i->task.push_back(t);
}

void Idle::invoke(Instance *, IsoCoord *, float) {

}

bool Idle::update(Instance *i, void *) {
	i->frame += inc_rate;
	if (i->hp <= 0) {
		i->frame = 0.0f;
		return true;
	}
	return false;
}

Idle::~Idle() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
