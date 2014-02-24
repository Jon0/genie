/*
 * Player.cpp
 *
 *  Created on: 31/07/2013
 *      Author: remnanjona
 */

#include <math.h>
#include "Player.h"

namespace std {

Player::Player(char r,  char g, char b) {
	// normalise colour vector
	float rf = r / 256.0, gf = g / 256.0, bf = b / 256.0;
	float d = sqrt(rf*rf + gf*gf + bf*bf);
	rf /= d;
	gf /= d;
	bf /= d;

	for (int i = 0; i < 16; ++i) {
		char rc = rf*((16-i-1)/16.0)*256.0, gc = gf*((16-i-1)/16.0)*256.0, bc = bf*((16-i-1)/16.0)*256.0;
		color[i] = (0xff << 24) + (rc << 16) + (gc << 8) + bc;
	}
}

Player::~Player() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
