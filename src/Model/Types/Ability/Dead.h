/*
 * Dead.h
 *
 *  Created on: 9/03/2014
 *      Author: remnanjona
 */

#ifndef DEAD_H_
#define DEAD_H_

#include "Idle.h"

namespace std {

class Dead: public Idle {
public:
	Dead(int);
	virtual ~Dead();

	virtual bool complete(Instance *, void *);
	virtual bool update(Instance *, void *);
};

} /* namespace std */

#endif /* DEAD_H_ */
