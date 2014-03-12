/*
 * Client.h
 *
 *  Created on: 10/03/2014
 *      Author: remnanjona
 */

#ifndef CLIENT_H_
#define CLIENT_H_

namespace std {

class EventQueue;
class GameEvent;

class Client {
public:
	EventQueue *event_queue;
	Client(EventQueue *);
	virtual ~Client();

	void toHost(GameEvent);
};

} /* namespace std */

#endif /* CLIENT_H_ */
