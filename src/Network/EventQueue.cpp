/*
 * EventQueue.cpp
 *
 *  Created on: 12/03/2014
 *      Author: remnanjona
 */

#include <iostream>

#include "EventQueue.h"

namespace std {



EventQueue::EventQueue(State *gs) {
	s = gs;
}

EventQueue::~EventQueue() {
	// TODO Auto-generated destructor stub
}

void EventQueue::startupWait() {
	cout << "waiting for startup event" << endl;
	while (events.empty()) {}

	applyAll();
}

void EventQueue::applyAll() {
	while (!events.empty()) {
		std::unique_lock<std::mutex> mlock(m);
		GameEvent event = events.front();
		event.apply(s);
		events.pop();
		mlock.unlock();

		if (event.type == "tick") break; // need to render
	}
}

} /* namespace std */
