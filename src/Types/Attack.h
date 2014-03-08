/*
 * Attack.h
 *
 *  Created on: 8/03/2014
 *      Author: remnanjona
 */

#ifndef ATTACK_H_
#define ATTACK_H_

#include "Ability.h"

namespace std {

/*
 * task requires some movement
 */
class Attack: public Move {
public:
	Attack(int);
	virtual ~Attack();

	virtual bool canInvoke(Instance *);
};

} /* namespace std */

#endif /* ATTACK_H_ */
