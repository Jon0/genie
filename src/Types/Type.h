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
#include "../Graphics/Frame.h"
#include "../Graphics/Circle.h"
#include "Ability.h"

namespace std {

class Instance;

class Type {
public:
	vector<Ability *> ability;
	int initial_hp;
	Player *owner;

	//Base *b .. define base for building or radius for unit
	float radius; // buildings dont have this
	Circle circle;

	Type(Player *, int);
	virtual ~Type();

	//Instance *newInstance();
	void addAbility(Ability *);
	Ability *getAbility(Instance *obj);
	Ability *getMove(float x, float y);
	Frame *getFrame(Resource *, int, int);

};

} /* namespace std */
#endif /* TYPE_H_ */
