/*
 * HealthBar.cpp
 *
 *  Created on: 15/03/2014
 *      Author: remnanjona
 */

#include "HealthBar.h"

namespace std {

HealthBar::HealthBar() {
	green.width = 30;
	green.height = 3;
	green.anchorx = 15;
	green.anchory = 2;
	int *image_data = new int[green.width * green.height];
	for (int i = 0; i < green.width * green.height; ++i)
		image_data[i] = 0xff00ff00;
	green.createTexture(image_data);
	delete image_data;

	red.width = 30;
	red.height = 3;
	red.anchorx = 15;
	red.anchory = 2;
	image_data = new int[red.width * red.height];
	for (int i = 0; i < red.width * red.height; ++i)
		image_data[i] = 0xff0000ff;
	red.createTexture(image_data);
	delete image_data;


}

HealthBar::~HealthBar() {
	// TODO Auto-generated destructor stub
}

void HealthBar::draw(ScreenCoord s, float p) {
	red.draw(s.x, s.y, -100);

	green.draw(s.x, s.y, 30 * p, 3, -110);
}

} /* namespace std */
