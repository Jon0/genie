/*
 * Client.cpp
 *
 *  Created on: 10/03/2014
 *      Author: remnanjona
 */


#include <iostream>
#include <thread>
#include <boost/array.hpp>
#include <boost/asio.hpp>

#include "Client.h"
#include "EventQueue.h"
#include "GameEvent.h"

using boost::asio::ip::tcp;

namespace std {

void client_thread(Client *c) {

	try {
		boost::asio::io_service io_service;

		tcp::resolver resolver(io_service);
		tcp::resolver::query query("localhost", "6564");
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		tcp::resolver::iterator end;

		tcp::socket socket(io_service);
		boost::system::error_code error = boost::asio::error::host_not_found;
		while (error && endpoint_iterator != end) {
			socket.close();
			socket.connect(*endpoint_iterator++, error);
		}
		if (error)
			throw boost::system::system_error(error);

	    for (;;)
	    {
	      //boost::array<char, 128> buf;
	    	boost::asio::streambuf buffer;
	    	boost::system::error_code error;

	      size_t len = read_until(socket, buffer, "\n", error);

	      if (error == boost::asio::error::eof)
	        break; // Connection closed cleanly by peer.
	      else if (error)
	        throw boost::system::system_error(error); // Some other error.

	      istream str(&buffer);
	      string s;
	      getline(str, s);

	      std::unique_lock<std::mutex> mlock(c->event_queue->m);
	      c->event_queue->events.push( GameEvent(s) );
	      //cout << "recieved " << s << endl;
	      mlock.unlock();     // unlock before notificiation to minimize mutex contention
	    }


	} catch (std::exception& e) {
		cerr << e.what() << endl;
	}

}

Client::Client(EventQueue *eq) {
	event_queue = eq;

	cout << "start client" << endl;

    thread t1(client_thread, this);
    t1.detach();
}

Client::~Client() {
	// TODO Auto-generated destructor stub
}

/*
 * return message to host
 */
void Client::toHost(GameEvent) {

}

} /* namespace std */
