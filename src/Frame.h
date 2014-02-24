/*
 * Frame.h
 *
 *  Created on: 6/07/2013
 *      Author: asdf
 */

#ifndef FRAME_H_
#define FRAME_H_

#include <GL/gl.h>

namespace std {

class Player;

struct SlpHead {
	char version [4];
	int frames;
	char comment [24];
};

struct FrameData {
	int command_offset, outline_offset, palette_offset,
		properties, width, height, anchor_x, anchor_y;
};

struct FrameBounds {
	short int *left;
	short int *right;
};

class Frame {
	GLuint texture;
	int *image_data;
	bool mirror;
	Player *owner;
public:
	int height, width, anchorx, anchory;
	Frame(Player *, unsigned char *, int, bool);
	void draw(int, int, int);
	int readCommand(int, int, unsigned char *);
	void fill(int, int, int, unsigned char *, bool, bool);
	virtual ~Frame();
};

} /* namespace std */
#endif /* FRAME_H_ */
