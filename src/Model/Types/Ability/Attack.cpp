/*
 * Attack.cpp
 *
 *  Created on: 8/03/2014
 *      Author: remnanjona
 */

#include <iostream>

#include "../../Path.h"
#include "../../Tile.h"
#include "../../Instance.h"
#include "../Type.h"
#include "Attack.h"

namespace std {

Attack::Attack(int gid, float r): Idle(gid) {
	range = r;
}

Attack::~Attack() {
	// TODO Auto-generated destructor stub
}

bool Attack::canInvoke(Instance *i, Instance *other) {
	return other != NULL && i->owner != other->owner && other->hp > 0;	// only on positive hp units
}

bool Attack::canInvoke(IsoCoord *) {
	return false;
}

void Attack::invoke(Instance *i, Instance *target) {
	task_arg t;
	t.ability = this;
	t.arg = target;
	i->task.push_back(t);
}

bool Attack::complete(Instance *, void *arg) {
	Instance *target = (Instance *) arg;

	return target->dead;
}

bool Attack::update(Instance *i, void *arg) {
	int xdir, ydir;

	// TODO target may be removed and be inaccessable memory
	Instance *target = (Instance *) arg;
	if (target->hp <= 0) {
		return true;
	}

	float sum = range + i->type->radius + target->type->radius + 0.05;
	if (i->dist(target) > sum) {
		i->setTask(&target->current, sum);
	}
	else {
		// create projectile
		target->hp--;
		if (target->hp <= 0) return true;
	}


	i->frame += inc_rate * 10.0f;
	return false;
}


} /* namespace std */
