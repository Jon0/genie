/*
 * Texture.h
 *
 *  Created on: 28/02/2014
 *      Author: remnanjona
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace std {

class Texture {
	GLuint texture;

public:
	int height, width, anchorx, anchory;

	Texture();
	virtual ~Texture();

	bool containsPoint(int, int);
	void createTexture(int *);
	void updateTexture(int *);
	void setPixel(int *, int, int, int);
	void draw(int x, int y, int z);
	void draw(int x, int y, int wid, int hei, int z);
};

} /* namespace std */

#endif /* TEXTURE_H_ */
