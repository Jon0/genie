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
	ma->path = new Path(i->on, i->gs->getTile(target->ne, target->se), target->ne - (int) target->ne, target->se - (int) target->se);
	ma->target = target;
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
	float dist = i->dist(ma->target);
	if (path->point.size() == 0 || dist <= ma->range) {
		return true;
	}


	// path following
	Tile *next = path->point.data()[path->step];
	IsoCoord ncoord;
	ncoord.ne = next->x;
	ncoord.se = next->y;

	bool complete = false;
	update_simple(i, ncoord);
	if ((int) i->current.ne == next->x && (int) i->current.se == next->y) {

		if (path->step < path->point.size() - 1) {
			path->step++;
		} else {
			complete = true;
		}

		i->on->removeObj(i);
		i->on = next;
		i->on->addObj(i);

	}

//	vector<Instance *> ins = i->nearbyIns();
//	for (vector<Instance *>::iterator iter = ins.begin(); iter != ins.end(); ++iter) {
//		float sum = (*iter)->type->radius + i->type->radius;
//		if ( i->dist((*iter)) < sum ) {
//			// direction vector iter -> i
//			float ne = i->current.ne - (*iter)->current.ne;
//			float se = i->current.se - (*iter)->current.se;
//			float d = sqrt(ne*ne + se*se) / speed;
//
//			if (d > 0) {
//				ne /= d;
//				se /= d;
//				i->current.ne += ne;
//				i->current.se += se;
//			}
//		}
//	}

	i->frame += inc_rate * 10.0f;
	return complete;
}

void Move::update_simple(Instance *i, IsoCoord target) {
	if ( i->dist(&target) < speed ) {
		i->current = target;
		return;
	}

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
