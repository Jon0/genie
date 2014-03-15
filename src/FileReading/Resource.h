/*
 * Resource.h
 *
 *  Created on: 6/07/2013
 *      Author: asdf
 */

#ifndef RESOURCE_H_
#define RESOURCE_H_

#include "../GenieData/Graphic.h"
#include "../Graphics/Frame.h"

namespace std {

class Player;

// TODO rename to GenieSLP oor merge with Graphic
class Resource {
	int frames;
	Frame **frame;
public:
	genie::Graphic *gr;
	Resource(Player *, unsigned char *);
	Resource(Player *, unsigned char *, genie::Graphic *);
	int getFrames();
	Frame *getFrame(int);
	virtual ~Resource();
};

} /* namespace std */
#endif /* RESOURCE_H_ */
