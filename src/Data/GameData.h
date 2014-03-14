/*
 * GameData.h
 *
 *  Created on: 14/07/2013
 *      Author: asdf
 */

//TODO unused class

#ifndef GAMEDATA_H_
#define GAMEDATA_H_

#include <stdlib.h>
#include <istream>
#include <iostream>
#include <stdio.h>

#include <string.h>
#include <assert.h>
#include <vector>

#include <zlib.h>


#define CHUNK 16384
#define SET_BINARY_MODE(file)

namespace std {

class GameData {
	istream *is;
	vector<char> data;
public:
	GameData();
	int decompress(FILE *);
	virtual ~GameData();
};

} /* namespace std */
#endif /* GAMEDATA_H_ */
