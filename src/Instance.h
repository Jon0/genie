/*
 * Instance.h
 *
 *  Created on: 9/07/2013
 *      Author: asdf
 */

#ifndef INSTANCE_H_
#define INSTANCE_H_

namespace std {

class Ability;
class Type;
class State;
class Tile;

class Instance {
	Ability *task;	// current task
public:
	Type *type;
	void *arg;
	float x, y, targetx, targety, frame;
	int direction;
	Tile *on;
	Instance(State *s, Type *, float, float);
	void setTask(Instance *);
	void setTask(float x, float y, Tile *);
	void update();
	void draw(int, int);
	virtual ~Instance();
};

} /* namespace std */
#endif /* INSTANCE_H_ */
