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
	Idle(int gid);
	virtual ~Idle();

	virtual void assignGraphic(Resource *);
	virtual bool comlpete();
	virtual bool canInvoke(Instance *);
	virtual void update(Instance *);
	virtual void draw(int, int, int, int);
};

} /* namespace std */
#endif /* IDLE_H_ */
