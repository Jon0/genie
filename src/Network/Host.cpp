/*
 * Host.cpp
 *
 *  Created on: 10/03/2014
 *      Author: remnanjona
 */

#include <iostream>
//#include <boost/array.hpp>
//#include <boost/asio.hpp>

#include "Host.h"

//using boost::asio::ip::tcp;

namespace std {

Host::Host() {
	// TODO Auto-generated constructor stub

	//try {
	//	boost::asio::io_service io_service;

	//	//A boost::asio::ip::tcp::acceptor object needs to be created to listen for new connections. It is initialised to listen on TCP port 13, for IP version 4.

	//	tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13));

	//	//This is an iterative server, which means that it will handle one connection at a time. Create a socket that will represent the connection to the client, and then wait for a connection.

	//	for (;;) {
	//		tcp::socket socket(io_service);
	//		acceptor.accept(socket);

	//		//A client is accessing our service. Determine the current time and transfer this information to the client.

	//		std::string message = "hello";

	//		boost::system::error_code ignored_error;
	//		boost::asio::write(socket, boost::asio::buffer(message),
	//				boost::asio::transfer_all(), ignored_error);
	//	}
	//}

	////Finally, handle any exceptions.

	//catch (std::exception& e) {
	//	std::cerr << e.what() << std::endl;
	//}

}

Host::~Host() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */