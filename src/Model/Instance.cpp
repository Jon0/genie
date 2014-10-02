/*
 * Instance.cpp
 *
 *  Created on: 9/07/2013
 *      Author: asdf
 */

#include <iostream>
#include <math.h>

#include "State.h"
#include "Tile.h"
#include "Path.h"
#include "Types/Ability/Dead.h"
#include "Types/Ability/Ability.h"
#include "Types/Type.h"
#include "Instance.h"

namespace std {

Instance::Instance(State *state, Type *t, float xi, float yi) {
	gs = state;
	type = t;

	state_id = state->getNextID();
	current.ne = xi;
	current.se = yi;
	direction = 0;
	owner = type->initial_owner;
	hp = type->unit->HitPoints;
	dead = false;
	frame = 0;
	on = state->getTile( (int)xi, (int)yi );

	setTask(NULL);
}

Instance::~Instance() {
	// TODO Auto-generated destructor stub
}

IsoCoord Instance::getIso() {
	return current;
}

Ability *Instance::getTask() {
	return task.back().ability;
}

float Instance::dist(Instance *other) {
	if ( !other ) {
		cout << "distance to null instance?" << endl;
		return 0;
	}
	float dx = other->current.ne - current.ne;
	float dy = other->current.se - current.se;
	return sqrt(dx*dx + dy*dy);
}

float Instance::dist(IsoCoord *point) {
	if ( !point ) {
		cout << "distance to null point?" << endl;
		return 0;
	}
	float dx = point->ne - current.ne;
	float dy = point->se - current.se;
	return sqrt(dx*dx + dy*dy);
}

void Instance::setTask(Instance *target) {
	if (dead) return;
	for (int i = 0; i < type->ability.size(); ++i) {
		if ( type->ability.data()[i]->canInvoke(this, target) ) {
			type->ability.data()[i]->invoke(this, target);
		}
	}
}

void Instance::setTask(IsoCoord *target, float radius) {
	if (dead) return;
	for (int i = 0; i < type->ability.size(); ++i) {
		if ( type->ability.data()[i]->canInvoke(target) ) {
			type->ability.data()[i]->invoke(this, target, radius);
		}
	}
}

void Instance::stopTask() {
	// stops any user controlable tasks
	while (task.size() > 2) task.pop_back();
}

bool Instance::update(State *s) {
	for (vector<task_arg>::iterator i = task.begin(); i != task.end(); ++i) {
		if ( (*i).ability->complete(this, (*i).arg) ) {
			task.erase(i, task.end());
			return task.empty();
		}
	}

	if ( task.back().ability->update(this, task.back().arg) ) {
		task.pop_back();
	}

	return task.empty(); // remove from game when no task
}

void Instance::draw(ScreenCoord sc) {
	Frame *f = task.back().ability->frame(direction, (int)frame);
	if (f) f->draw(sc.x, sc.y, 0);
}

bool Instance::pointCheck(ScreenCoord sc) {
	int i = (int)frame;
	Frame *f = task.back().ability->frame(direction, i);

	if (f) {
		int x = f->anchorx + sc.x;
		int y = f->anchory - sc.y;
		//cout << "f " << i%task->group_size << ", " << x << "/" << f->width << ", " << y << "/" << f->height << endl;

		if ( f->containsPoint(x, y) ) {
			int *c = &f->image_data[x + y * f->width];
			return c > 0;
		}
	}
	return false;
}

vector<Instance *> Instance::nearbyIns() {
	vector<Instance *> ins;

	for (int i = 0; i < on->objs(); ++i) {
		Instance *obj = on->getObj(i);
		if (obj != this) {
			ins.push_back(obj);
		}
	}

	// need to check adjacent tiles
	for (int a = 0; a < 4; ++a) {
		Tile *t = on->getAdj(a);
		if (t) {
			for (int i = 0; i < t->objs(); ++i) {
				Instance *obj = t->getObj(i);
				if (obj != this) {
					ins.push_back(obj);
				}
			}
			t = on->getAdj((a + 1) % 4);
			if (t) {
				for (int i = 0; i < t->objs(); ++i) {
					Instance *obj = t->getObj(i);
					if (obj != this) {
						ins.push_back(obj);
					}
				}
			}
		}

	}


	return ins;

}

void Instance::updateTile() {
	int ne = current.ne;
	int se = current.se;
	if (on->x != ne || on->y != se) {
		on->removeObj(this);
		on = gs->getTile(ne, se);
		on->addObj(this);
	}
}

} /* namespace std */
