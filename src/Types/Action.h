/*
 * Action.h
 *
 *  Created on: 9/07/2013
 *      Author: asdf
 */

#ifndef ACTION_H_
#define ACTION_H_

namespace std {

class Action {
public:
	virtual bool comlpete() = 0;
	virtual ~Action() {}

};

} /* namespace std */


#endif /* ACTION_H_ */
