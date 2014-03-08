/*
 * Instance.cpp
 *
 *  Created on: 9/07/2013
 *      Author: asdf
 */
#include <iostream>

#include "Model/State.h"
#include "Model/Tile.h"
#include "Model/Path.h"
#include "Types/Ability.h"
#include "Types/Type.h"
#include "Instance.h"

namespace std {

Instance::Instance(State *state, Type *t, float xi, float yi) {
	frame = 0;
	type = t;

	current.ne = xi;
	current.se = yi;
	target.ne = current.ne;
	target.se = current.se;
	direction = 0;
	hp = type->initial_hp;
	task = type->getAbility(NULL);
	arg = NULL;
	state->addObj(this);
	on = state->getTile( (int)xi, (int)yi );
}

IsoCoord Instance::getIso() {
	return current;
}

Ability *Instance::getTask() {
	return task;
}

void Instance::setTask(Instance *i) {
	task = type->getAbility(i);
}

void Instance::setTask(float x, float y, Tile *end) {
	Ability *a = type->getMove(x, y);

	/* test the ability exist Check(sc)) return obj;
	 *  */
	if (a) {
		task = a;
		arg = new Path(on, end, x-(int)x, y-(int)y);
		target.ne = x;
		target.se = y;
	}
}

void Instance::update() {
	task->update(this);
}

void Instance::draw(ScreenCoord sc) {
	int i = (int)frame;
	task->draw(sc.x, sc.y, direction, i);
}

bool Instance::pointCheck(ScreenCoord sc) {
	int i = (int)frame;
	Frame *f = task->frame(direction, i);

	if (f) {
		int x = f->anchorx + sc.x;
		int y = f->anchory - sc.y;
		cout << "f " << i%task->group_size << ", " << x << "/" << f->width << ", " << y << "/" << f->height << endl;

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
