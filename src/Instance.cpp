/*
 * Instance.cpp
 *
 *  Created on: 9/07/2013
 *      Author: asdf
 */

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
	task = type->getMove(x, y);
	arg = new Path(on, end, x-(int)x, y-(int)y);
	target.ne = x;
	target.se = y;
}

void Instance::update() {
	task->update(this);
}

void Instance::draw(ScreenCoord sc) {
	int i = (int)frame;
	task->draw(sc.x, sc.y, direction, i);
}

Instance::~Instance() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
