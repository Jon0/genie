/*
 * Blend.cpp
 *
 *  Created on: 6/03/2014
 *      Author: remnanjona
 */

#include <iostream>
#include <fstream>

#include "../def.h"
#include "../Graphics/Frame.h"
#include "Blend.h"

namespace std {

Blend::Blend(Frame *a) {
	width = a->width;
	height = a->height;
	anchorx = a->anchorx;
	anchory = a->anchory;

	/* copy image data */
	image_data = new int [width * height];
	for (int i = 0; i < width * height; ++i) {
		image_data[i] = a->image_data[i];
	}
}

void Blend::mix(Frame *a, unsigned char *blend) {
	for (int i = 0; i < width * height; ++i) {
		float percent = blend[i] / 128.0;
		//image_data[i] = image_data[i] * percent + a->image_data[i] * (1-percent);

		color *c1 = (color *)&image_data[i];
		color *c2 = (color *)&a->image_data[i];
		c1->r = c1->r * percent + c2->r * (1-percent);
		c1->g = c1->g * percent + c2->g * (1-percent);
		c1->b = c1->b * percent + c2->b * (1-percent);


		//image_data[i] = image_data[i]/2;// | (int)blend[i];
	}
}

void Blend::makeTexture() {
	createTexture(image_data);
}

Blend::~Blend() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
