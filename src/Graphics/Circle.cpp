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
	width = 200;
	height = 100;
	anchorx = 100;
	anchory = 50;
	int *image_data = new int[width*height];

	for (int i = 0; i < width; ++i) {
		for (int j = 0; j < height; ++j) {

			int dx = i-anchorx;
			int dy = j-anchory;
			float distance = dx*dx/3.0 + dy*dy; // distance from centre
			cout << distance << endl;

			if (180 < distance && distance < 200) {
				image_data[i + j * width] = 0xffffffff;
			}
			else {
				image_data[i + j * width] = 0x00000000;
			}
		}
	}


	createTexture(image_data);
}

Circle::~Circle() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
