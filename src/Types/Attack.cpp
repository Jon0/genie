/*
 * Attack.cpp
 *
 *  Created on: 8/03/2014
 *      Author: remnanjona
 */

#include <iostream>

#include "../Model/Path.h"
#include "../Model/Tile.h"
#include "../Resource.h"
#include "../Instance.h"
#include "Attack.h"

namespace std {

Attack::Attack(int gid): Move(gid, 0.01) {

}

Attack::~Attack() {
	// TODO Auto-generated destructor stub
}

bool Attack::canInvoke(Instance *i) {
	return i != NULL && i->hp > 0;	// only on positive hp units
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

bool Attack::update(Instance *i, void *arg) {
	int xdir, ydir;

	// TODO target may be removed and be inaccessable memory
	Instance *target = (Instance *) arg;
	if (target->hp <= 0) {
		return true;
	}
	if (i->dist(target) > 4.0f) {
		i->setTask(&target->current, 4.0f);
	}
	else {
		// create projectile
		target->hp--;
		if (target->hp <= 0) return true;
	}


	i->frame += 0.3;
	return false;
}


} /* namespace std */
