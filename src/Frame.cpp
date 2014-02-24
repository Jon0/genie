/*
 * Frame.cpp
 *
 *  Created on: 6/07/2013
 *      Author: asdf
 */

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "def.h"
#include "Model/Player.h"
#include "Frame.h"

namespace std {

Frame::Frame(Player *player, unsigned char *data, int index, bool m) {
	owner = player;
	mirror = m;

	// copy head information
	FrameData *head = (FrameData *)&data[index*sizeof(FrameData)+sizeof(SlpHead)];
	height = head->height;
	width = head->width;
	if (mirror) anchorx = width - head->anchor_x;
	else anchorx = head->anchor_x;
	anchory = head->anchor_y;

	// get offset of outline and commands
	short int *outline = (short int *)&data[head->outline_offset];
	int *command = (int *)&data[head->command_offset];
	image_data = new int[head->width*head->height];
	for (int i = 0; i < head->width*head->height; ++i) {
		image_data[i] = 0x00000000;
	}

	/* fill each line from commands */
	for (int y = 0; y < head->height; ++y) {
		if ( outline[2*y] >= 1000 ) {
			cout << "skip?" << endl;
		}
		int f = readCommand(outline[2*y], y, &data[command[y]]);
		if ( f + outline[2*y + 1] != head->width ) {
			cout << "error" << endl;
			break;
		}
	}	// end height

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_RECTANGLE_NV, texture);
	glTexImage2D(GL_TEXTURE_RECTANGLE_NV, 0, GL_RGBA, head->width, head->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

	// select modulate to mix texture with color for shading
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glTexParameteri( GL_TEXTURE_RECTANGLE_NV, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_RECTANGLE_NV, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	delete[] image_data;
}

int Frame::readCommand(int x, int y, unsigned char *data) {
	unsigned char c = data[0], nc;
	int width, read_length;

	/*read extra byte for length */
	switch (c & 0x0f) {
	case 0:
	case 4:
	case 8:
	case 12:
		width = ((int) (c & 0xff)) >> 2;
		read_length = width;
		fill(x, y, width, &data[1], false, false);
		break;
	case 1:
	case 5:
	case 9:
	case 13:
		width = ((int) (c & 0xff)) >> 2;
		read_length = 0;
		break;
	case 2:
		// copy long
		nc = data[1];
		width = (((int) (c & 0xf0)) << 4) + (int) (nc & 0xff);
		read_length = 1+width;
		fill(x, y, width, &data[2], false, false);
		break;
	case 3:
		// skip long
		nc = data[1];
		width = (((int) (c & 0xf0)) << 4) + (int) (nc & 0xff);
		read_length = 1;
		break;
	case 11:
		// shadow
		// fill(f, across, down, (byte)131, length);
		if ((c & 0xf0) == 0) {
			nc = data[1];
			width = nc;
			read_length = 1;
		} else {
			width = (int) (c & 0xf0) >> 4;
			read_length = 0;
		}
		break;
	case 7:
		// fill block
		if ((c & 0xf0) == 0) {
			nc = data[1];
			width = nc;
			read_length = 2;
			fill(x, y, width, &data[2], false, true);
		} else {
			width = (int) (c & 0xf0) >> 4;
			read_length = 1;
			fill(x, y, width, &data[1], false, true);
		}
		break;
	case 6:
		// copy player colour
		if ((c & 0xf0) == 0) {
			width = data[1];
			read_length = 1+width;
			fill(x, y, width, &data[2], true, true);
		} else {
			width = (int) (c & 0xf0) >> 4;
			read_length = width;
			fill(x, y, width, &data[1], true, true);
		}
		break;
	case 10:
		// fill single colour
		if ((c & 0xf0) == 0) {
			width = data[1];
			read_length = 2;
			fill(x, y, width, &data[2], true, true);
		} else {
			width = (int) (c & 0xf0) >> 4;
			read_length = 1;
			fill(x, y, width, &data[1], true, true);
		}
		break;
	case 14:
		if (((c & 0x0ff) == 0x4e) || ((c & 0x0ff) == 0x6e)) {
			width = 1;
			read_length = 0;
		} else if (((c & 0x0ff) == 0x5e) || ((c & 0x0ff) == 0x7e)) {
			nc = data[1];
			width = nc;
			read_length = 1;
		} else {
			cout << "error in read: " << ((int) (c & 0x0ff)) << endl;
		}
		break;
	case 15:
		return x;
	} //end switch

	return readCommand(x + width, y, &data[1+read_length]);
}

void Frame::fill(int x, int y, int length, unsigned char *d, bool p, bool single) {
	for (int i = 0; i < length; ++i) {
		int *addr;
		if (mirror) addr = &image_data[(height-y-1) * width + (width-x-1) - i];
		else addr = &image_data[(height-y-1) * width + x + i];

		if (!owner && p) *addr = 0xffffffff;
		else if (owner && p && single) *addr = owner->color[d[0]];
		else if (owner && p) *addr = owner->color[d[i]];
		else if (single) *addr = color_table[d[0]];
		else *addr = color_table[d[i]];	// needs to lookup colour
	}
}

void Frame::draw(int x, int y, int z) {
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

Frame::~Frame() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
