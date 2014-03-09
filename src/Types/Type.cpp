/*
 * Type.cpp
 *
 *  Created on: 9/07/2013
 *      Author: asdf
 */

#include <iostream>

#include "../Model/Player.h"
#include "../Instance.h"
#include "Idle.h"
#include "Move.h"
#include "Type.h"

namespace std {

Type::Type(Player *p, Ability *initial, bool building) {
	// maybe mapping abilities to graphics is better
	ability.push_back( initial );
	owner = p;
	radius = 0.5;
	initial_hp = 100;
	build = building;
}

Type::~Type() {
	// TODO Auto-generated destructor stub
}

void Type::addAbility(Ability *a) {

//	ability.push_back( new Idle( file->getResource(p, offset + 2, true) ) );
	ability.push_back( a );

}

} /* namespace std */
