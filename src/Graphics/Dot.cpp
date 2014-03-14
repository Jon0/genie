/*
 * Dot.cpp
 *
 *  Created on: 14/03/2014
 *      Author: remnanjona
 */

#include "Dot.h"

namespace std {

Dot::Dot(int color) {
	width = 4;
	height = 4;
	anchorx = 0;
	anchory = 0;
	int *image_data = new int[width*height];

	for (int i = 0; i < width*height; ++i) {
		image_data[i] = color;
	}

	createTexture(image_data);
}

Dot::~Dot() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
