/*
 * Host.cpp
 *
 *  Created on: 10/03/2014
 *      Author: remnanjona
 */

#include <stdlib.h>
#include <iostream>
#include <thread>
#include <chrono>

#include <boost/array.hpp>
#include <boost/asio.hpp>

#include "Host.h"

using boost::asio::ip::tcp;

namespace std {

boost::system::error_code ignored_error;

void host_thread(Host *host) {
	int random = rand();
	ostringstream convert;
	convert << random;
	string message = "startup "+convert.str()+"\n";


	try {
		boost::asio::io_service io_service;

		//A boost::asio::ip::tcp::acceptor object needs to be created to listen for new connections. It is initialised to listen on TCP port 13, for IP version 4.

		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 6564));

		//This is an iterative server, which means that it will handle one connection at a time. Create a socket that will represent the connection to the client, and then wait for a connection.

		for (;;) {
			tcp::socket *socket = new tcp::socket(io_service);
			acceptor.accept(*socket);

			cout << "new connection" << endl;

			//A client is accessing our service. Determine the current time and transfer this information to the client.
			boost::asio::write(*socket, boost::asio::buffer(message),
					boost::asio::transfer_all(), ignored_error);

			host->connections.push_back(socket);
		}
	}
	//Finally, handle any exceptions.
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}

void broadcast_thread(Host *host) {
	string message = "tick\n";
	//int tick_count = 0;

	for (;;) {
		// recieve from clients
		for (list<tcp::socket *>::iterator i = host->connections.begin(); i != host->connections.end(); ++i) {
			boost::asio::streambuf buffer;
			boost::system::error_code error;

			size_t a = (*i)->available();
			if (a) {
				size_t len = read_until(*(*i), buffer, "\n", error);

				if (error == boost::asio::error::eof)
					break; // Connection closed cleanly by peer.
				else if (error)
					throw boost::system::system_error(error); // Some other error.

				istream str(&buffer);
				string s;
				while (getline(str, s)) {
					host->broadcast(s);
				}
			}
		}

		// process message queue
		std::unique_lock<std::mutex> mlock(host->queue_mutex);
		while ( !host->broadcast_queue.empty() ) {
			string next = host->broadcast_queue.front();
			host->broadcast_queue.pop();

			// send to all
			for (list<tcp::socket *>::iterator i = host->connections.begin(); i != host->connections.end(); ++i) {
				boost::asio::write(*(*i), boost::asio::buffer(next),
						boost::asio::transfer_all(), ignored_error);

			}
		}
		mlock.unlock();

		// send tick to all
		for (list<tcp::socket *>::iterator i = host->connections.begin(); i != host->connections.end(); ++i) {
			boost::asio::write(*(*i), boost::asio::buffer(message), //+" "+to_string(tick_count)+"\n"
					boost::asio::transfer_all(), ignored_error);

		}
		//tick_count++;

	    std::chrono::milliseconds dura( 50 );
	    std::this_thread::sleep_for( dura );
	}
}

Host::Host() {
	cout << "start server" << endl;

    thread t1(host_thread, this);
    t1.detach();

    thread bc(broadcast_thread, this);
    bc.detach();
}

Host::~Host() {
	// TODO Auto-generated destructor stub
}

void Host::broadcast(string s) {
	std::unique_lock<std::mutex> mlock(queue_mutex);
	broadcast_queue.push(s + "\n");
	mlock.unlock();
}

} /* namespace std */
