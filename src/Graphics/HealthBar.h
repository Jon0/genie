/*
 * HealthBar.h
 *
 *  Created on: 15/03/2014
 *      Author: remnanjona
 */

#ifndef HEALTHBAR_H_
#define HEALTHBAR_H_

#include "../def.h"
#include "Texture.h"

namespace std {

class HealthBar {
	Texture green;
	Texture red;

public:
	HealthBar();
	virtual ~HealthBar();

	void draw(ScreenCoord, float);
};

} /* namespace std */

#endif /* HEALTHBAR_H_ */
