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

class Resource;

class Idle: public Ability {
	Resource *image;
	int group_size;
public:
	Idle(Resource *);
	virtual bool comlpete();
	virtual void update(Instance *);
	virtual void draw(int, int, int, int);
	virtual ~Idle();
};

} /* namespace std */
#endif /* IDLE_H_ */
