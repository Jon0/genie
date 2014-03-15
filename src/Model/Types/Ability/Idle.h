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
public:
	float inc_rate;
	Idle(int gid);
	virtual ~Idle();

	virtual void assignGraphic(Resource *);
	virtual bool canInvoke(Instance *, Instance *);
	virtual bool canInvoke(IsoCoord *);
	virtual void invoke(Instance *, Instance *);
	virtual void invoke(Instance *, IsoCoord *, float);
	virtual bool complete(Instance *, void *);
	virtual bool update(Instance *, void *);

	void setDirection(Instance *i, float, float);
};

} /* namespace std */
#endif /* IDLE_H_ */
