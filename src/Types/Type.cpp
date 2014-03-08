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

Type::Type(Player *p, int offset) {
	// maybe mapping abilities to graphics is better
	ability.push_back( new Idle( offset ) );
	owner = p;
	radius = 0.5;
	initial_hp = 100;
}

Type::~Type() {
	// TODO Auto-generated destructor stub
}

void Type::addAbility(Ability *a) {

//	ability.push_back( new Idle( file->getResource(p, offset + 2, true) ) );
	ability.push_back( a );

}

/* TODO: are these methods not used? */
Ability *Type::getAbility(Instance *obj) {
	// find an ability able to be used

	if (obj == NULL) return ability.data()[0];
	else {
		cout << "attack" << endl;
		return ability.data()[0];
	}

}

Ability *Type::getMove(float x, float y) {
	if (ability.size() < 2) {
		cout << "no move" << endl;
		return NULL;
	}
	return ability.data()[1];
}

Frame *Type::getFrame(Resource *r, int direction, int frame) {
	int group_size = r->getFrames() / 8;
	return r->getFrame(direction * group_size + frame % group_size);
}

} /* namespace std */
