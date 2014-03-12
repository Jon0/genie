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

void EventQueue::applyAll() {
	cout << "apply all " << endl;

	bool apply = true;



    std::unique_lock<std::mutex> mlock(m);
    cond.wait(mlock);

	while (apply) {
		if (!events.empty()) {
			GameEvent event = events.front();
			event.apply(s);
			events.pop();
			if (event.type == "tick") {
				apply = false; // go draw frame
			}
		}
	}
	mlock.unlock();
}

} /* namespace std */
