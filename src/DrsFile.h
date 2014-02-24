/*
 * DrsFile.h
 *
 *  Created on: 6/07/2013
 *      Author: asdf
 */

#ifndef DRSFILE_H_
#define DRSFILE_H_

#include <iostream>
#include <fstream>
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
public:
	DrsFile(const char *);
	Resource *getResource(int, bool);
	Resource *getResource(Player *, int index, bool mirror);
	virtual ~DrsFile();
};

} /* namespace std */
#endif /* DRSFILE_H_ */
