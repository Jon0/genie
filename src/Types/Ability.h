/*
 * Action.h
 *
 *  Created on: 9/07/2013
 *      Author: asdf
 */

#ifndef ACTION_H_
#define ACTION_H_

#include "../Resource.h"

namespace std {

class Frame;
class Instance;

class Ability {
public:
	int graphic_id, group_size, directions;
	Resource *image;

	virtual ~Ability() {}
	virtual void assignGraphic(Resource *) = 0;
	virtual bool comlpete() = 0;
	virtual bool canInvoke(Instance *) = 0;
	virtual void update(Instance *) = 0;
	virtual void draw(int, int, int, int) = 0;

	Frame *frame(int direction, int tick) {
		if (group_size == 0) return NULL;

		return image->getFrame(direction * group_size + tick % group_size);
	}
};

} /* namespace std */


#endif /* ACTION_H_ */
