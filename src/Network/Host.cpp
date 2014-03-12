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
			boost::system::error_code ignored_error;
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

	for (;;) {

		//cout << host->connections.size() << " connections " << endl;

		for (list<tcp::socket *>::iterator i = host->connections.begin(); i != host->connections.end(); ++i) {
			boost::system::error_code ignored_error;
			boost::asio::write(*(*i), boost::asio::buffer(message),
					boost::asio::transfer_all(), ignored_error);

		}

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

    //Join the thread with the main thread
    //t1.join();
}

Host::~Host() {
	// TODO Auto-generated destructor stub
}

void Host::broadcast(string s) {
	broadcast_queue.push(s + "\n");
}

} /* namespace std */
