/*
 * Instance.cpp
 *
 *  Created on: 9/07/2013
 *      Author: asdf
 */

#include <iostream>
#include <math.h>

#include "Model/State.h"
#include "Model/Tile.h"
#include "Model/Path.h"
#include "Types/Dead.h"
#include "Types/Ability.h"
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
	hp = type->initial_hp;
	frame = 0;
	on = state->getTile( (int)xi, (int)yi );

	setTask(NULL);
}

IsoCoord Instance::getIso() {
	return current;
}

Ability *Instance::getTask() {
	return task.back().ability;
}

float Instance::dist(Instance *other) {
	int dx = other->current.ne - current.ne;
	int dy = other->current.se - current.se;
	return sqrt(dx*dx + dy*dy);
}

float Instance::dist(IsoCoord *point) {
	int dx = point->ne - current.ne;
	int dy = point->se - current.se;
	return sqrt(dx*dx + dy*dy);
}

void Instance::setTask(Instance *target) {
	for (int i = 0; i < type->ability.size(); ++i) {
		if ( type->ability.data()[i]->canInvoke(target) ) {
			type->ability.data()[i]->invoke(this, target);
		}
	}
}

void Instance::setTask(IsoCoord *target, float radius) {
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
	// TODO update all tasks?

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

		if (0 <= x && x < f->width && 0 <= y && y < f->height) {
			int *c = &f->image_data[x + y * f->width];
			return c > 0;
		}
	}
	return false;
}

Instance::~Instance() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
