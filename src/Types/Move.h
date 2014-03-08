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

class Resource;

class Move: public Ability {
	float speed;
public:
	Move(int, float);
	virtual ~Move();

	virtual void assignGraphic(Resource *);
	virtual bool comlpete();
	virtual bool canInvoke(Instance *);
	virtual void update(Instance *);
	void update_simple(Instance *i, float, float);
	virtual void draw(int, int, int, int);

};

} /* namespace std */
#endif /* MOVE_H_ */
