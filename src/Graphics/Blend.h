/*
 * Blend.h
 *
 *  Created on: 6/03/2014
 *      Author: remnanjona
 */

#ifndef BLEND_H_
#define BLEND_H_

#include "Texture.h"

namespace std {

class Frame;

class Blend: public Texture {
public:
	int *image_data;

	Blend(Frame *);
	virtual ~Blend();

	void mix(Frame *, unsigned char *);
	void makeTexture();

};

} /* namespace std */

#endif /* BLEND_H_ */
