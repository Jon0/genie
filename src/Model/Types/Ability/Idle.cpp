/*
 * Idle.cpp
 *
 *  Created on: 14/07/2013
 *      Author: asdf
 */

#include <iostream>

#include "../../Instance.h"
#include "Idle.h"

namespace std {

Idle::Idle(int gid) {
	graphic_id = gid;
	image = NULL;
	group_size = 0;
	inc_rate = 0.0;
}

Idle::~Idle() {
	// TODO Auto-generated destructor stub
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
	inc_rate = res->gr->FrameRate;
}

bool Idle::canInvoke(Instance *i, Instance *other) {
	return other == NULL;
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

bool Idle::complete(Instance *i, void *v) {
	if (i->hp <= 0) {
		i->frame = 0.0f;
		i->dead = true;
		return true;
	}
	return false;
}

//TODO split into autotasking ability
bool Idle::update(Instance *i, void *v) {

	vector<Instance *> ins = i->nearbyIns();
	for (vector<Instance *>::iterator iter = ins.begin(); iter != ins.end(); ++iter) {
		if ( (*iter)->owner != i->owner ) {
			i->setTask((*iter));
			break;
		}
	}

	i->frame += inc_rate;
	return complete(i, v);
}

void Idle::setDirection(Instance *i, float xdir, float ydir) {
	if (xdir > 0 && ydir > 0) i->direction = 6;
	else if (xdir > 0 && ydir < 0) i->direction = 4;
	else if (xdir > 0 && ydir == 0) i->direction = 7;
	else if (xdir < 0 && ydir > 0) i->direction = 0;
	else if (xdir < 0 && ydir < 0) i->direction = 2;
	else if (xdir < 0 && ydir == 0) i->direction = 1;
	else if (xdir == 0 && ydir > 0) i->direction = 5;
	else if (xdir == 0 && ydir < 0) i->direction = 3;
}



} /* namespace std */
