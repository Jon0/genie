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
	Resource *image;
	int group_size;
	float speed;
public:
	Move(Resource *);
	virtual bool comlpete();
	virtual void update(Instance *);
	void update_simple(Instance *i, float, float);
	virtual void draw(int, int, int, int);
	virtual ~Move();
};

} /* namespace std */
#endif /* MOVE_H_ */
