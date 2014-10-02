/*
 * Move.cpp
 *
 *  Created on: 14/07/2013
 *      Author: remnanjona
 */

#include <math.h>

#include "../../../FileReading/Resource.h"
#include "../../Path.h"
#include "../../State.h"
#include "../../Instance.h"
#include "../Type.h"
#include "Move.h"

namespace std {

Move::Move(int gid, float s): Idle(gid) {
	speed = s;
}

bool Move::canInvoke(Instance *, Instance *) {
	return false;
}

bool Move::canInvoke(IsoCoord *) {
	return true;
}

void Move::invoke(Instance *, Instance *) {

}

void Move::invoke(Instance *i, IsoCoord *target, float radius) {
	// TODO where is path deleted?
	// TODO append existing path if shift clicked
	move_args *ma = new move_args();
	ma->path = new Path(i->on, target);

	if (ma->path->length() > 0) ma->next_target = &ma->path->next()->position;
	else {
		ma->next_target = NULL;
	}

	ma->final_target = target;
	ma->range = radius;

	task_arg t;
	t.ability = this;
	t.arg = ma;
	i->task.push_back(t);
}

bool Move::complete(Instance *, void *) {
	return false;
}

bool Move::update(Instance *i, void *arg) {
	int xdir, ydir;
	move_args *ma = (move_args *) arg;
	Path *path = ma->path;

	/*
	 * path empty, or within range
	 */
	float dist_to_final = i->dist(ma->final_target);
	if (dist_to_final < ma->range || !ma->next_target) {
		delete ma->path;
		return true;
	}

	bool complete = false;
	float remain = speed;
	float dist_to_next = i->dist(ma->next_target);
	if ( dist_to_next < speed ) {
		i->current = *ma->next_target;
		remain -= dist_to_next;
	}

	update_simple(i, *ma->next_target, remain);
	if (i->current.ne == ma->next_target->ne && i->current.se == ma->next_target->se) {

		if (path->length() <= 0) {
			complete = true;
		}
		else {
			ma->next_target = &ma->path->next()->position;
		}
	}
	i->updateTile();
	i->frame += inc_rate * 10.0f;

	if (complete) {
		delete ma->path;
	}
	return complete;
}

void Move::update_simple(Instance *i, IsoCoord target, float speed) {

	// direction vector i -> target
	float ne = target.ne - i->current.ne;
	float se = target.se - i->current.se;
	float d = sqrt(ne * ne + se * se) / speed;
	if (d > 0) {
		ne /= d;
		se /= d;
		i->current.ne += ne;
		i->current.se += se;
	}
	setDirection(i, ne, se);
}

Move::~Move() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
