/*
 * Client.cpp
 *
 *  Created on: 10/03/2014
 *      Author: remnanjona
 */


#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

#include "Client.h"

using boost::asio::ip::tcp;

namespace std {

Client::Client() {
	try
	  {
	    boost::asio::io_service io_service;

	    tcp::resolver resolver(io_service);
	    tcp::resolver::query query("localhost", "6564");
	    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
	    tcp::resolver::iterator end;

	    tcp::socket socket(io_service);
	    boost::system::error_code error = boost::asio::error::host_not_found;
	    while (error && endpoint_iterator != end)
	    {
	      socket.close();
	      socket.connect(*endpoint_iterator++, error);
	    }
	    if (error)
	      throw boost::system::system_error(error);

	    for (;;)
	    {
	      boost::array<char, 128> buf;
	      boost::system::error_code error;

	      size_t len = socket.read_some(boost::asio::buffer(buf), error);

	      if (error == boost::asio::error::eof)
	        break; // Connection closed cleanly by peer.
	      else if (error)
	        throw boost::system::system_error(error); // Some other error.

	      cout.write(buf.data(), len);
	    }
	  }
	  catch (std::exception& e)
	  {
	    cerr << e.what() << endl;
	  }

}

Client::~Client() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
