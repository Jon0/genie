/*
 * Instance.h
 *
 *  Created on: 9/07/2013
 *      Author: asdf
 */

#ifndef INSTANCE_H_
#define INSTANCE_H_

#include <vector>

#include "../def.h"

namespace std {

class Ability;
class Type;
class Player;
class State;
class Tile;

struct task_arg {
	Ability *ability;
	void *arg;	// arguments required for current task
};

/*
 * break into Instance and ClickableInstance?
 */
class Instance {
public:
	int state_id;
	State *gs;
	Type *type;
	vector<task_arg> task;	// stack of tasks to complete
	Player *owner;
	// TODO when task ends all task above get popped

	/* TODO these should be arguments too */
	float frame;
	IsoCoord current;
	int direction, hp;
	bool dead;
	Tile *on;

	Instance(State *s, Type *, float, float);
	virtual ~Instance();

	IsoCoord getIso();
	Ability *getTask();
	float dist(Instance *);
	float dist(IsoCoord *point);
	void setTask(Instance *);
	void setTask(IsoCoord *, float);
	void stopTask();
	bool update(State *);
	void draw(ScreenCoord);
	bool pointCheck(ScreenCoord);
	vector<Instance *> nearbyIns();
	void updateTile();
};

} /* namespace std */
#endif /* INSTANCE_H_ */
