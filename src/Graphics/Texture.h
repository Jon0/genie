/*
 * Texture.h
 *
 *  Created on: 28/02/2014
 *      Author: remnanjona
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <GL/gl.h>

namespace std {

class Texture {
	GLuint texture;

public:
	int height, width, anchorx, anchory;

	Texture();
	virtual ~Texture();

	void createTexture(int *);
	void draw(int x, int y, int z);
};

} /* namespace std */

#endif /* TEXTURE_H_ */
