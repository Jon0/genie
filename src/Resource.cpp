/*
 * Resource.cpp
 *
 *  Created on: 6/07/2013
 *      Author: asdf
 */

#include <iostream>
#include "Resource.h"

namespace std {

Resource::Resource(Player *p, int id, unsigned char *data, bool mirror) {
	SlpHead *head = (SlpHead *)data;

	// set total number of frames;
	if (mirror) {
		// produce extra frames
		float group = head->frames / 5.0;
		frames = (int)group * 8;
		frame = new Frame *[frames];

		for (int direction = 0; direction < 5; ++direction) {
			for (int i = 0; i < (int)group; ++i) {
				frame[(int)group*direction + i] = new Frame(p, data, (int)(direction*group) + i, false);

				 // reflect if 0 < direction < 4
				if (0 < direction && direction < 4 ) {
					frame[(int)group*(direction+4) + i] = new Frame(p, data, (int)(direction*group) + i, true);
				}

			}
		}
	}
	else {
		frames = head->frames;
		frame = new Frame *[frames];
		for (int i = 0; i < frames; ++i) {
			frame[i] = new Frame(p, data, i, false);
		}
	}

	delete data;
}

int Resource::getFrames() {
	return frames;
}

Frame *Resource::getFrame(int index) {
	return frame[index % frames];
}

Resource::~Resource() {

}

} /* namespace std */
