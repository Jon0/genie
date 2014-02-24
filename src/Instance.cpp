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
	x = xi;
	y = yi;
	targetx = x;
	targety = y;
	direction = 0;
	task = type->getAbility(NULL);
	arg = NULL;
	state->addObj(this);
	on = state->getTile( (int)xi, (int)yi );
}

void Instance::setTask(Instance *i) {
	task = type->getAbility(i);
}

void Instance::setTask(float x, float y, Tile *end) {
	task = type->getMove(x, y);
	arg = new Path(on, end, x-(int)x, y-(int)y);
	targetx = x;
	targety = y;
}

void Instance::update() {
	task->update(this);
}

void Instance::draw(int view_x, int view_y) {
	int i = (int)frame;
	//type->getFrame(state, direction, i)->draw(x, y);
	task->draw(view_x+(x+y)*48, view_y+(x-y-1)*24, direction, i);


}

Instance::~Instance() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
