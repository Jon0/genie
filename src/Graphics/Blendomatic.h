/*
 * Blendomatic.h
 *
 *  Created on: 6/03/2014
 *      Author: remnanjona
 */

#ifndef BLENDOMATIC_H_
#define BLENDOMATIC_H_

namespace std {

struct head_data {
	int modes;
	int tile_angles;
};

struct mode_data {
	int blocksize;
	char *flags;
	char *data1;
	char **data2;
};

class Blendomatic {
public:
	head_data head;
	mode_data *modes;

	unsigned char ***iso_data;

	Blendomatic();
	virtual ~Blendomatic();

	unsigned char *getAngle(int);
};

} /* namespace std */

#endif /* BLENDOMATIC_H_ */
