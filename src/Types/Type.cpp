/*
 * Type.cpp
 *
 *  Created on: 9/07/2013
 *      Author: asdf
 */

#include "../Model/Player.h"
#include "../Instance.h"
#include "Idle.h"
#include "Move.h"
#include "Type.h"

namespace std {

Type::Type(Player *p, DrsFile *file, int offset) {
	// maybe mapping abilities to graphics is better
	ability.push_back( new Idle( file->getResource(p, offset + 2, true) ) );
	ability.push_back( new Move( file->getResource(p, offset + 4, true) ) );
	speed = 0.03;
	radius = 0.5;
}

Ability *Type::getAbility(Instance *obj) {
	// find an ability able to be used
	return ability.data()[0];
}

Ability *Type::getMove(float x, float y) {
	return ability.data()[1];
}

Frame *Type::getFrame(Resource *r, int direction, int frame) {
	int group_size = r->getFrames() / 8;
	return r->getFrame(direction * group_size + frame % group_size);
}

Type::~Type() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
