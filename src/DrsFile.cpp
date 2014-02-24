/*
 * DrsFile.cpp
 *
 *  Created on: 6/07/2013
 *      Author: asdf
 */

#include "DrsFile.h"

namespace std {

DrsFile::DrsFile(const char *filename) {
	file.open(filename, ios::in | ios::binary);
	file.seekg(0, ios::beg);
	file.read((char *) &head, sizeof(DrsHeader));

	/* read table data*/
	table = new DrsTable[head.tables];
	for (unsigned int t = 0; t < head.tables; t++) {
		file.read((char *) &table[t], sizeof(DrsTable));
	}

	/* read all entry data */
	entry = new DrsEntry *[head.tables];
	for (unsigned int t = 0; t < head.tables; t++) {
		entry[t] = new DrsEntry[table[t].size];
		for (unsigned int e = 0; e < table[t].size; e++) {
			file.read((char *) &entry[t][e], sizeof(DrsEntry));
		}
	}
}

Resource *DrsFile::getResource(int index, bool mirror) {
	return getResource(NULL, index, mirror);
}

Resource *DrsFile::getResource(Player *p, int index, bool mirror) {
	DrsEntry *selected = &entry[0][index];
	unsigned char *block = new unsigned char[selected->size];
	file.seekg (selected->offset, ios::beg);
	file.read((char *)block, selected->size);
	return new Resource(p, selected->id, block, mirror);
}

DrsFile::~DrsFile() {
	for (unsigned int t = 0; t < head.tables; t++) {
		delete entry[t];
	}
	delete entry;
	delete table;
	file.close();
}

} /* namespace std */
