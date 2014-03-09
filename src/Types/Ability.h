/*
 * Action.h
 *
 *  Created on: 9/07/2013
 *      Author: asdf
 */

#ifndef ACTION_H_
#define ACTION_H_

#include "../def.h"
#include "../Resource.h"

namespace std {

class Frame;
class Instance;
class State;

class Ability {
public:
	int graphic_id, group_size, directions;
	Resource *image;

	virtual ~Ability() {}
	virtual void assignGraphic(Resource *) = 0;
	virtual bool comlpete() = 0;
	virtual bool canInvoke(Instance *) = 0;	// parameter is the target of invokation
	virtual bool canInvoke(IsoCoord *) = 0;
	virtual void invoke(Instance *, Instance *) = 0;
	virtual void invoke(Instance *, IsoCoord *, float) = 0;
	virtual bool update(Instance *, void *) = 0; // return true when task is complete

	Frame *frame(int direction, int tick) {
		if (group_size == 0) {
			return NULL;
		}

		return image->getFrame(direction * group_size + tick % group_size);
	}
};

} /* namespace std */


#endif /* ACTION_H_ */
