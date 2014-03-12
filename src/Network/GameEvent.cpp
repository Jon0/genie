/*
 * GameEvent.cpp
 *
 *  Created on: 12/03/2014
 *      Author: remnanjona
 */

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "../Model/State.h"
#include "../Instance.h"
#include "GameEvent.h"

namespace std {

GameEvent::GameEvent(string s) {

	// string split
	istringstream iss(s);
	vector<string> tokens{istream_iterator<string>{iss},
	         istream_iterator<string>{}};


	if (tokens.size() == 0) {
		cerr << "0 sized token" << endl;
		return;
	}

	type = tokens[0];

	if (type == "startup") {
		startup_event *event = new startup_event();
		event->seed = atoi(tokens[1].c_str());
		arg = event;
	}

	if (type == "move") {
		move_event *event = new move_event();
		event->instance = atoi(tokens[1].c_str());
		event->loc.ne = atof(tokens[2].c_str());
		event->loc.se = atof(tokens[3].c_str());
		arg = event;
	}

	if (type == "interact") {
		interact_event *event = new interact_event();
		event->instance_a = atoi(tokens[1].c_str());
		event->instance_b = atoi(tokens[2].c_str());
		arg = event;
	}

}

GameEvent::~GameEvent() {
	// TODO Auto-generated destructor stub
}

void GameEvent::apply(State *gs) {
	//cout << "apply event " << type << endl;
	if (type == "startup") {
		startup_event *event = (startup_event *)arg;
		gs->startup( event->seed );
	}
	else if (type == "tick") {
		gs->update();
	}
	else if (type == "move") {
		move_event *event = (move_event *)arg;
		Instance *ins = gs->fromID(event->instance);
		if (ins) {
			ins->stopTask();
			ins->setTask(&event->loc, 0.0f);
		}
		else {
			cerr << "instance not found" << endl;
		}
	}
	else if (type == "interact") {
		interact_event *event = (interact_event *)arg;
		Instance *ins1 = gs->fromID(event->instance_a);
		Instance *ins2 = gs->fromID(event->instance_b);
		if (ins1 && ins2) {
			ins1->stopTask();
			ins1->setTask(ins2);
		}
		else {
			cerr << "instance not found" << endl;
		}
	}

}

} /* namespace std */
