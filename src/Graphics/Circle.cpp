/*
 * Circle.cpp
 *
 *  Created on: 28/02/2014
 *      Author: remnanjona
 */

#include <iostream>
#include <stdlib.h>

#include "Circle.h"

namespace std {

Circle::Circle() {

}

Circle::~Circle() {
	// TODO Auto-generated destructor stub
}

void Circle::create(float radius) {
	width = 100;
	height = 50;
	anchorx = 50;
	anchory = 25;
	int *image_data = new int[width*height];
	int max = radius * 671;
	int min = radius * 614;

	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {

			int dx = i-anchorx;
			int dy = j-anchory;
			float distance = dx*dx/3.0 + dy*dy; // distance from centre

			if (min < distance && distance < max) {
				image_data[i + j * width] = 0xffffffff;
			}
			else {
				image_data[i + j * width] = 0x00000000;
			}
		}
	}


	createTexture(image_data);
}

} /* namespace std */
