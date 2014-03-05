/*
 * Texture.cpp
 *
 *  Created on: 28/02/2014
 *      Author: remnanjona
 */

#include "Texture.h"

namespace std {

Texture::Texture() {
	// TODO Auto-generated constructor stub

}

Texture::~Texture() {
	// TODO Auto-generated destructor stub
}

void Texture::createTexture(int *image_data) {
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_RECTANGLE_NV, texture);
	glTexImage2D(GL_TEXTURE_RECTANGLE_NV, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

	// select modulate to mix texture with color for shading
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glTexParameteri( GL_TEXTURE_RECTANGLE_NV, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_RECTANGLE_NV, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
}

void Texture::updateTexture(int *image_data) {
	glBindTexture(GL_TEXTURE_RECTANGLE_NV, texture);
	glTexImage2D(GL_TEXTURE_RECTANGLE_NV, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
}

void Texture::draw(int x, int y, int z) {
	glPushMatrix();
	glTranslatef(x-anchorx, y-height+anchory, -y-z);
	glBindTexture(GL_TEXTURE_RECTANGLE_NV, texture);
	glBegin( GL_QUADS );
	glTexCoord2i( 0, 0 );
	glVertex3i( 0, 0, 0 );
	glTexCoord2i( width, 0 );
	glVertex3i( width, 0, 0 );
	glTexCoord2i( width, height );
	glVertex3i( width, height, 0 );
	glTexCoord2i( 0, height );
	glVertex3i( 0, height, 0 );
	glEnd();
	glPopMatrix();
}

} /* namespace std */
