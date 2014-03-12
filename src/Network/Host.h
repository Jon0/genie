/*
 * Host.h
 *
 *  Created on: 10/03/2014
 *      Author: remnanjona
 */

#ifndef HOST_H_
#define HOST_H_

#include <list>
#include <string>
#include <queue>

#include <boost/array.hpp>
#include <boost/asio.hpp>

namespace std {

class Host {
public:
	queue<string> broadcast_queue;
	list<boost::asio::ip::tcp::socket *> connections;

	Host();
	virtual ~Host();

	void broadcast(string);
};

} /* namespace std */

#endif /* HOST_H_ */
