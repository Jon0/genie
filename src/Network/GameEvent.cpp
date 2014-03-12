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
#include "GameEvent.h"

namespace std {

GameEvent::GameEvent(string s) {

	// string split
	istringstream iss(s);
	vector<string> tokens{istream_iterator<string>{iss},
	         istream_iterator<string>{}};

	type = tokens[0];

	if (type == "startup") {
		startup_event *event = new startup_event();
		event->seed = atoi(tokens[1].c_str());
		arg = event;
	}

}

GameEvent::~GameEvent() {
	// TODO Auto-generated destructor stub
}

void GameEvent::apply(State *gs) {
	cout << "apply event " << type << endl;
	if (type == "startup") {
		gs->startup(0);
	}
	else if (type == "tick") {
		//gs->update();
	}

}

} /* namespace std */
