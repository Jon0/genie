/*
 * Resource.h
 *
 *  Created on: 6/07/2013
 *      Author: asdf
 */

#ifndef RESOURCE_H_
#define RESOURCE_H_

#include "Frame.h"

namespace std {

class Player;

class Resource {
	int frames;
	Frame **frame;
public:
	Resource(Player *, int, unsigned char *, bool);
	int getFrames();
	Frame *getFrame(int);
	virtual ~Resource();
};

} /* namespace std */
#endif /* RESOURCE_H_ */
