/*
 * Type.cpp
 *
 *  Created on: 9/07/2013
 *      Author: asdf
 */

#include <iostream>

#include "../Player.h"
#include "../Instance.h"
#include "Ability/Attack.h"
#include "Ability/Dead.h"
#include "Ability/Idle.h"
#include "Ability/Move.h"
#include "Type.h"

namespace std {

Type::Type(Player *p, genie::Unit *u) {
	initial_owner = p;
	unit = u;
	cout << "add type " << unit->Name << endl;

	// parse unit attributes
	if (u->Type == genie::UT_Creatable) {
		ability.push_back( new Dead( unit->DyingGraphic.first) );
		ability.push_back( new Idle( unit->StandingGraphic.first ) );
		ability.push_back( new Move( unit->DeadFish.WalkingGraphic.first, unit->Speed / 15.0f ) );
		ability.push_back( new Attack( unit->Projectile.AttackGraphic, unit->Projectile.MaxRange ) );
	}
	else {
		ability.push_back( new Idle( unit->StandingGraphic.first ) );
	}
	radius = unit->SizeRadius.first;
	circle.create(radius);
}

Type::Type(Player *p, int i): Type(p, &p->civ->Units.data()[i]) {}

Type::~Type() {
	// TODO Auto-generated destructor stub
}

void Type::addAbility(Ability *a) {

//	ability.push_back( new Idle( file->getResource(p, offset + 2, true) ) );
	ability.push_back( a );

}

} /* namespace std */
