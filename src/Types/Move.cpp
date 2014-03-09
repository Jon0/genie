/*
 * Move.cpp
 *
 *  Created on: 14/07/2013
 *      Author: remnanjona
 */

#include "../Model/Path.h"
#include "../Model/State.h"
#include "../Resource.h"
#include "../Instance.h"
#include "Type.h"
#include "Move.h"

namespace std {

Move::Move(int gid, float s) {
	graphic_id = gid;
	image = NULL;
	group_size = 0;
	speed = s;
}

void Move::assignGraphic(Resource *res) {
	image = res;

	if ( res->getFrames()  >= 8) {
		group_size = res->getFrames() / 8;
	}
	else {
		group_size = res->getFrames();
	}
}

bool Move::comlpete() {
	return true;
}

bool Move::canInvoke(Instance *) {
	return false;
}

bool Move::canInvoke(IsoCoord *) {
	return true;
}

void Move::invoke(Instance *, Instance *) {

}

void Move::invoke(Instance *i, IsoCoord *target, float radius) {
	move_args *ma = new move_args();
	ma->path = new Path(i->on, i->gs->getTile(target->ne, target->se), target->ne - (int) target->ne, target->se - (int) target->se);
	ma->target = target;
	ma->range = radius;

	task_arg t;
	t.ability = this;
	t.arg = ma;
	i->task.push_back(t);
}


bool Move::update(Instance *i, void *arg) {
	int xdir, ydir;

	move_args *ma = (move_args *) arg;
	Path *path = ma->path;

	/*
	 * path empty, or within range
	 */
	if (path->point.size() == 0 || i->dist(ma->target) <= ma->range) {
		return true;
	}


	Tile *next = path->point.data()[path->step];
	update_simple(i, next->x, next->y);

	bool complete = false;
	if ((int)i->current.ne == next->x && (int)i->current.se == next->y) {
		if (path->step < path->point.size()-1) {
			path->step++;
		}
		else {
			complete = true;
		}
		i->on->removeObj(i);
		i->on = next;
		i->on->addObj(i);
	}

	i->frame += 0.5;
	return complete;
}

void Move::update_simple(Instance *i, float targetx, float targety) {
		int xdir, ydir;

		if (i->current.ne < targetx-speed) {
			i->current.ne += speed;
			xdir = 1;
		}
		else if (i->current.ne > targetx+speed) {
			i->current.ne -= speed;
			xdir = -1;
		}
		else {
			i->current.ne = targetx;
			xdir = 0;
		}
		if (i->current.se < targety-speed) {
			i->current.se += speed;
			ydir = 1;
		}
		else if (i->current.se > targety+speed) {
			i->current.se -= speed;
			ydir = -1;
		}
		else {
			i->current.se = targety;
			ydir = 0;
		}

		if (xdir > 0 && ydir > 0) i->direction = 6;
		else if (xdir > 0 && ydir < 0) i->direction = 4;
		else if (xdir > 0 && ydir == 0) i->direction = 7;
		else if (xdir < 0 && ydir > 0) i->direction = 0;
		else if (xdir < 0 && ydir < 0) i->direction = 2;
		else if (xdir < 0 && ydir == 0) i->direction = 1;
		else if (xdir == 0 && ydir > 0) i->direction = 5;
		else if (xdir == 0 && ydir < 0) i->direction = 3;
}

Move::~Move() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
