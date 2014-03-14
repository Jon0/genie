/*
 * Player.cpp
 *
 *  Created on: 31/07/2013
 *      Author: remnanjona
 */

#include <math.h>

#include "../Graphics/Dot.h"
#include "../Types/Dead.h"
#include "../Types/Idle.h"
#include "../Types/Move.h"
#include "../Types/Attack.h"
#include "Player.h"

namespace std {

Player::Player(GenieCiv *gc, unsigned char r, unsigned char g, unsigned char b) {
	civ = gc;

	// normalise colour vector
	float rf = r / 256.0, gf = g / 256.0, bf = b / 256.0;
	float d = sqrt(rf*rf + gf*gf + bf*bf);
	rf /= d;
	gf /= d;
	bf /= d;

	for (int i = 0; i < 16; ++i) {
		float shade = (16.0+i)/32.0;
		char rc = rf*shade*256.0, gc = gf*shade*256.0, bc = bf*shade*256.0;

		//char rc = 256.0 - rf*((16-i-1)/16.0)*256.0, gc = 256.0 - gf*((16-i-1)/16.0)*256.0, bc = 256.0 - bf*((16-i-1)/16.0)*256.0;
		color[i] = (0xff << 24) + (rc << 16) + (gc << 8) + bc;
	}

	color_dot = new Dot(color[0]);

}

Player::~Player() {
	// TODO Auto-generated destructor stub
}

Type *Player::createType(int i) {
	GenieUnit *u = &civ->Units.data()[i];

	cout << u->u_data->name1 << endl;
	cout << u->u_data->head.graphic_default << endl;

	int k =  181; //u->u_data->head.graphic_default;

	Type *random = new Type(this, new Idle( k+1 ), false);
	random->addAbility( new Idle( k+2 ) );
	random->addAbility( new Move( k+4, 0.08 ) );
	random->addAbility( new Attack( k ) );




	return random;
}

} /* namespace std */
