/*
 * GameEvent.h
 *
 *  Created on: 12/03/2014
 *      Author: remnanjona
 */

#ifndef GAMEEVENT_H_
#define GAMEEVENT_H_

#include <string>

namespace std {

class State;

struct startup_event {
	int seed;
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
