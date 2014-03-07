/*
 * Blendomatic.cpp
 *
 *  Created on: 6/03/2014
 *      Author: remnanjona
 */

#include <iostream>
#include <fstream>

#include "Blendomatic.h"

namespace std {

Blendomatic::Blendomatic() {
	//	uint32: nr of blending modes (9)
	//	uint32: nr of tiles(31)
	//	for (i=0;i<nr of blendingmodes)
	//	{
	//	  uint32: tilesize(2353, that`s 48*49 pixels);
	//	  31bytes: tileflags(they are all 1);
	//	  4*blocksize bytes which are 32 interleaved tiles representing 1 bit alpha masks, don't know how this is used for
	//	  for (j=0;j<nr of tiles)
	//	  {
	//	    blocksize bytes: the actual tile pixels; starting from the top .. rendered in the isometric tile format
	//	  }
	//	}
	//


	ifstream file;
	file.open("resource/blendomatic.dat", ios::in | ios::binary);
	file.seekg(0, ios::beg);

	file.read((char *) &head, sizeof(head_data));
	modes = new mode_data [head.modes];
	for (int m = 0; m < head.modes; ++m) {
		file.read((char *) &modes[m].blocksize, sizeof(int));
		modes[m].flags = new char [head.tile_angles];
		file.read((char *) modes[m].flags, sizeof(char) * head.tile_angles);
		modes[m].data1 = new char [4 * modes[m].blocksize];
		file.read((char *) modes[m].data1, sizeof(char) * 4 * modes[m].blocksize);
		modes[m].data2 = new char *[head.tile_angles];
		for (int t = 0; t < head.tile_angles; ++t) {
			modes[m].data2[t] = new char [modes[m].blocksize];
			file.read((char *) modes[m].data2[t], sizeof(char) * modes[m].blocksize);
		}
	}
	file.close();

	iso_data = new unsigned char **[head.modes];
	for (int m = 0; m < head.modes; ++m) {
		iso_data[m] = new unsigned char *[head.tile_angles];
		for (int t = 0; t < head.tile_angles; ++t) {
			int width = 97, height = 49, ind = 0;
			unsigned char *image_data = iso_data[m][t] = new unsigned char [width * height];
			for (int i = 0; i < width * height; ++i) {
				image_data[i] = 0;
			}

			for (int y = 0; y < height/2; ++y) {
				for (int x = width/2 - 2*y; x < width/2 + 2*y + 1; ++x) {
					image_data[x + width * y] = modes[m].data2[t][ind];
					ind++;
				}
			}
			for (int y = 0; y < height/2; ++y) {
				for (int x = 2*y; x < width - 2*y; ++x) {
					image_data[x + width * (y+height/2)] = modes[m].data2[t][ind];
					ind++;
				}
			}
		}
	}

}

Blendomatic::~Blendomatic() {
	// TODO Auto-generated destructor stub
}

unsigned char *Blendomatic::getAngle(int a) {
	if (a == 1) return iso_data[0][8];
	if (a == 2) return iso_data[0][12];
	if (a == 3) return iso_data[0][4];
	return iso_data[0][0];
}

} /* namespace std */
