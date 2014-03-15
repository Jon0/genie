/*
 * Type.h
 *
 *  Created on: 9/07/2013
 *      Author: asdf
 */

#ifndef TYPE_H_
#define TYPE_H_

#include <vector>

#include "../../GenieData/Unit.h"
#include "../../Graphics/Circle.h"

#include "Ability/Dead.h"
#include "Ability/Idle.h"
#include "Ability/Move.h"
#include "Ability/Attack.h"



namespace std {

/*
 * Types are a pair (Player, Unit)
 */
class Type {
public:
	vector<Ability *> ability;
	Player *initial_owner;
	genie::Unit *unit;

	Circle circle; // TODO move to view
	float radius;

	Type(Player *, genie::Unit *);
	Type(Player *, int);
	virtual ~Type();

	void addAbility(Ability *);
};

} /* namespace std */
#endif /* TYPE_H_ */
