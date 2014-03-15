/*
 * Player.h
 *
 *  Created on: 31/07/2013
 *      Author: remnanjona
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>

#include "../GenieData/Civ.h"

namespace std {

class Dot;

class Player {
public:
	string name;
	genie::Civ *civ;
	int color[16];
	Dot *color_dot;

	Player(genie::Civ *, unsigned char, unsigned char, unsigned char);
	virtual ~Player();
};

} /* namespace std */
#endif /* PLAYER_H_ */
