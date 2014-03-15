/*
 * Attack.h
 *
 *  Created on: 8/03/2014
 *      Author: remnanjona
 */

#ifndef ATTACK_H_
#define ATTACK_H_

#include "Idle.h"

namespace std {

class Attack: public Idle {
	float range;
public:
	Attack(int, float);
	virtual ~Attack();

	virtual bool canInvoke(Instance *, Instance *);
	virtual bool canInvoke(IsoCoord *);
	virtual void invoke(Instance *i, Instance *target);
	virtual bool complete(Instance *, void *);
	virtual bool update(Instance *i, void *);
};

} /* namespace std */

#endif /* ATTACK_H_ */
