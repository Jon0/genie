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
	    for (;;)
	    {
	    	boost::asio::streambuf buffer;
	    	boost::system::error_code error;

			size_t len = read_until(c->tcp_socket, buffer, "\n", error);

			if (error == boost::asio::error::eof)
				break; // Connection closed cleanly by peer.
			else if (error)
				throw boost::system::system_error(error); // Some other error.

			istream str(&buffer);
			string s;
			while (getline(str, s)) {

				if (s.length() > 0) {
					std::unique_lock<std::mutex> mlock(c->event_queue->m);
					c->event_queue->events.push(GameEvent(s));
					//cout << "recieved " << s << endl;
					mlock.unlock(); // unlock before notificiation to minimize mutex contention
				}
			}
		}

	} catch (std::exception& e) {
		cerr << "client thread error " << e.what() << endl;
	}

}

Client::Client(EventQueue *eq, const char *connect_to): tcp_socket(io_service) {
	cout << "connecting to " << connect_to << endl;
	event_queue = eq;
	try {
		tcp::resolver resolver(io_service);
		tcp::resolver::query query(connect_to, "6564");
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		tcp::resolver::iterator end;

		boost::system::error_code error = boost::asio::error::host_not_found;
		while (error && endpoint_iterator != end) {
			tcp_socket.close();
			tcp_socket.connect(*endpoint_iterator++, error);
		}
		if (error)
			throw boost::system::system_error(error);

		cout << "start client thread" << endl;
		thread t1(client_thread, this);
	    t1.detach();

	} catch (std::exception& e) {
		cerr << e.what() << endl;
	}
}

Client::Client(EventQueue *eq) : Client(eq, "localhost") {}

Client::~Client() {
	// TODO Auto-generated destructor stub
}

/*
 * return message to host
 */
void Client::toHost(string message) {
	boost::system::error_code ignored_error_a;
	boost::asio::write(tcp_socket, boost::asio::buffer(message + "\n"),
			boost::asio::transfer_all(), ignored_error_a);
}

} /* namespace std */
