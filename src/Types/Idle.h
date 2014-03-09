/*
 * Idle.h
 *
 *  Created on: 14/07/2013
 *      Author: asdf
 */

#ifndef IDLE_H_
#define IDLE_H_

#include "Ability.h"

namespace std {

class Idle: public Ability {
	float inc_rate;
public:
	Idle(int gid);
	virtual ~Idle();

	virtual void assignGraphic(Resource *);
	virtual bool comlpete();
	virtual bool canInvoke(Instance *);
	virtual bool canInvoke(IsoCoord *);
	virtual void invoke(Instance *, Instance *);
	virtual void invoke(Instance *, IsoCoord *, float);
	virtual bool update(Instance *, void *);
};

} /* namespace std */
#endif /* IDLE_H_ */
