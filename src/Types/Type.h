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
	vector<Ability *> ability;	// functions would be better than classes
public:
	Circle circle;
	float radius;
	int graphic_id;

	Type(Player *, DrsFile *, int);
	Type(Player *, DrsFile *, int, int);
	virtual ~Type();

	//Instance *newInstance();
	Ability *getAbility(Instance *obj);
	Ability *getMove(float x, float y);
	Frame *getFrame(Resource *, int, int);

};

} /* namespace std */
#endif /* TYPE_H_ */
