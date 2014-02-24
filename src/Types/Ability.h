/*
 * Action.h
 *
 *  Created on: 9/07/2013
 *      Author: asdf
 */

#ifndef ACTION_H_
#define ACTION_H_

namespace std {

class Instance;

class Ability {
public:
	virtual bool comlpete() = 0;
	virtual void update(Instance *) = 0;
	virtual void draw(int, int, int, int) = 0;
	virtual ~Ability() {}

};

} /* namespace std */


#endif /* ACTION_H_ */
