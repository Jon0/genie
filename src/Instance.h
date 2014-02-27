/*
 * Instance.h
 *
 *  Created on: 9/07/2013
 *      Author: asdf
 */

#ifndef INSTANCE_H_
#define INSTANCE_H_

#include "def.h"

namespace std {

class Ability;
class Type;
class State;
class Tile;

class Instance {
	Ability *task;	// current task
public:
	Type *type;
	void *arg;	// arguments required for current task
	float frame;
	IsoCoord current, target;
	int direction;
	Tile *on;

	Instance(State *s, Type *, float, float);
	IsoCoord getIso();
	Ability *getTask();
	void setTask(Instance *);
	void setTask(float x, float y, Tile *);
	void update();
	void draw(ScreenCoord);
	virtual ~Instance();
};

} /* namespace std */
#endif /* INSTANCE_H_ */
