/*
 * Player.h
 *
 *  Created on: 31/07/2013
 *      Author: remnanjona
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "../Data/unit.h"
#include "../Types/Type.h"

namespace std {

class Dot;

class Player {
public:
	string name;
	GenieCiv *civ;
	int color[16];
	Dot *color_dot;

	Player(GenieCiv *, unsigned char, unsigned char, unsigned char);
	virtual ~Player();

	Type *createType(int);
};

} /* namespace std */
#endif /* PLAYER_H_ */
