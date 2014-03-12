/*
 * GameEvent.h
 *
 *  Created on: 12/03/2014
 *      Author: remnanjona
 */

#ifndef GAMEEVENT_H_
#define GAMEEVENT_H_

#include <string>

#include "../def.h"

namespace std {

class State;

struct startup_event {
	int seed;
};

struct move_event {
	int instance;
	IsoCoord loc;
};

struct interact_event {
	int instance_a;
	int instance_b;
};

class GameEvent {
public:
	string type;
	void *arg;
	GameEvent(string);
	virtual ~GameEvent();

	void apply(State *);
};

} /* namespace std */

#endif /* GAMEEVENT_H_ */
