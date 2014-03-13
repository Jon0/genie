/*
 * Client.h
 *
 *  Created on: 10/03/2014
 *      Author: remnanjona
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace std {

class EventQueue;
class GameEvent;

class Client {
public:
	boost::asio::io_service io_service;
	tcp::socket tcp_socket;
	EventQueue *event_queue;
	Client(EventQueue *, const char *);
	Client(EventQueue *);
	virtual ~Client();

	void toHost(string);
};

} /* namespace std */

#endif /* CLIENT_H_ */
