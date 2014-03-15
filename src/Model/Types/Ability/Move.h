/*
 * Move.h
 *
 *  Created on: 14/07/2013
 *      Author: remnanjona
 */

#ifndef MOVE_H_
#define MOVE_H_

#include "Ability.h"

namespace std {

class Path;
class Resource;

struct move_args {
	Path *path;
	IsoCoord *next_target; // the next waypoint
	IsoCoord *final_target; // the next waypoint
	float range;
};

class Move: public Idle {
	float speed;
public:
	Move(int, float);
	virtual ~Move();
	virtual bool canInvoke(Instance *, Instance *);
	virtual bool canInvoke(IsoCoord *);
	virtual void invoke(Instance *, Instance *);
	virtual void invoke(Instance *, IsoCoord *, float);
	virtual bool complete(Instance *, void *);
	virtual bool update(Instance *, void *);
	void update_simple(Instance *i, IsoCoord, float);
};

} /* namespace std */
#endif /* MOVE_H_ */
