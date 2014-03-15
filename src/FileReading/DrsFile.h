/*
 * DrsFile.h
 *
 *  Created on: 6/07/2013
 *      Author: asdf
 */

#ifndef DRSFILE_H_
#define DRSFILE_H_

#include <fstream>
#include <iostream>
#include <map>

#include "../GenieData/Graphic.h"
#include "Resource.h"

namespace std {

struct DrsEntry {
	unsigned int id, offset, size;
};

struct DrsTable {
	char type[4];
	unsigned int offset, size;
};

struct DrsHeader {
	char comment[40], version[4], type[12];
	unsigned int tables, offset;
};

class DrsFile {
	ifstream file;
	DrsHeader head;
	DrsTable *table;
	DrsEntry **entry;
	map<int, int> slpItems;
public:
	DrsFile(const char *);
	virtual ~DrsFile();

	int resCount();
	Resource *getResource(int);
	Resource *getResource(Player *, int);
	Resource *getSlpFromId(Player *, genie::Graphic *);

};

} /* namespace std */
#endif /* DRSFILE_H_ */
