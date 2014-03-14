/*
 * Resource.h
 *
 *  Created on: 6/07/2013
 *      Author: asdf
 */

#ifndef RESOURCE_H_
#define RESOURCE_H_

#include "Graphics/Frame.h"

namespace std {

class Player;

// TODO rename to GenieSLP
class Resource {
	int frames;
	Frame **frame;
public:
	int res_id;
	Resource(Player *, int, unsigned char *, bool);
	int getFrames();
	Frame *getFrame(int);
	virtual ~Resource();
};

} /* namespace std */
#endif /* RESOURCE_H_ */
