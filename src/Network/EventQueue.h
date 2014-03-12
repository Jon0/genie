/*
 * EventQueue.h
 *
 *  Created on: 12/03/2014
 *      Author: remnanjona
 */

#ifndef EVENTQUEUE_H_
#define EVENTQUEUE_H_

#include <queue>
#include <mutex>
#include <condition_variable>

#include "GameEvent.h"

namespace std {

class State;

class EventQueue {
public:
	State *s;
	queue<GameEvent> events;
	mutex m;
	condition_variable cond;

	EventQueue(State *);
	virtual ~EventQueue();

	void startupWait();
	void applyAll();
};

} /* namespace std */

#endif /* EVENTQUEUE_H_ */
