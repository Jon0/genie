/*
 * Player.h
 *
 *  Created on: 31/07/2013
 *      Author: remnanjona
 */

#ifndef PLAYER_H_
#define PLAYER_H_

namespace std {

class Dot;

class Player {
public:
	int color[16];
	Dot *color_dot;
	Player(unsigned char, unsigned char, unsigned char);
	virtual ~Player();
};

} /* namespace std */
#endif /* PLAYER_H_ */
