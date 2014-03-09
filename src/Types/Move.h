/*
 * Move.h
 *
 *  Created on: 14/07/2013
 *      Author: remnanjona
 */

#ifndef MOVE_H_
#define MOVE_H_

#include "../def.h"
#include "Ability.h"

namespace std {

class Path;
class Resource;

struct move_args {
	Path *path;
	IsoCoord *target;
	float range;
};

class Move: public Ability {
	float speed;
public:
	Move(int, float);
	virtual ~Move();

	virtual void assignGraphic(Resource *);
	virtual bool comlpete();
	virtual bool canInvoke(Instance *);
	virtual bool canInvoke(IsoCoord *);
	virtual void invoke(Instance *, Instance *);
	virtual void invoke(Instance *, IsoCoord *, float);
	virtual bool update(Instance *, void *);
	void update_simple(Instance *i, float, float);
};

} /* namespace std */
#endif /* MOVE_H_ */
