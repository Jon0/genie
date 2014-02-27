/*
 * Move.cpp
 *
 *  Created on: 14/07/2013
 *      Author: remnanjona
 */

#include "../Model/Path.h"
#include "../Resource.h"
#include "../Instance.h"
#include "Type.h"
#include "Move.h"

namespace std {

Move::Move(Resource *res) {
	image = res;
	group_size = res->getFrames() / 8;
}

bool Move::comlpete() {
	return true;
}

void Move::update(Instance *i) {
	float speed = i->type->speed;
	int xdir, ydir;

	Path *path = (Path *)i->arg;
	if (path->point.size() == 0) {
		i->setTask(NULL);
		return;
	}


	Tile *next = path->point.data()[path->step];
	update_simple(i, next->x, next->y);


	if ((int)i->current.ne == next->x && (int)i->current.se == next->y) {
		if (path->step < path->point.size()-1) {
			path->step++;
		}
		else {
			i->setTask(NULL);
		}
		i->on->removeObj(i);
		i->on = next;
		i->on->addObj(i);
	}

	i->frame += 0.5;
}

void Move::update_simple(Instance *i, float targetx, float targety) {
	float speed = i->type->speed;
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

void Move::draw(int x, int y, int direction, int tick) {
	image->getFrame(direction * group_size + tick % group_size)->draw(x, y, 0);
	//cout << off[direction] + tick % dir[direction] << endl;
}

Move::~Move() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
