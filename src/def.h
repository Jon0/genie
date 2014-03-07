/*
 * def.h
 *
 *  Created on: 26/07/2013
 *      Author: remnanjona
 */

#ifndef DEF_H_
#define DEF_H_

extern int color_table[256];

struct ScreenCoord {
	int x, y;
};

struct IsoCoord {
	float ne, se;
};

struct Pointf {
	float x, y;
};

struct Pointi {
	int x, y;
};

struct color {
	unsigned char b, g, r, a;
};


#endif /* DEF_H_ */
