/*
 * Type.h
 *
 *  Created on: 9/07/2013
 *      Author: asdf
 */

#ifndef TYPE_H_
#define TYPE_H_

#include <vector>
#include "../DrsFile.h"
#include "../Resource.h"
#include "../Frame.h"
#include "Ability.h"

namespace std {

class Instance;

class Type {
	vector<Ability *> ability;	// functions would be better than classes
public:
	float radius, speed;
	Type(Player *, DrsFile *, int);
	//Instance *newInstance();
	Ability *getAbility(Instance *obj);
	Ability *getMove(float x, float y);
	Frame *getFrame(Resource *, int, int);
	virtual ~Type();
};

} /* namespace std */
#endif /* TYPE_H_ */
