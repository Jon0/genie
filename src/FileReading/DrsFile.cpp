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

	if (!file) {
		cout << "could not find " << filename << endl;
		return;
	}

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

			// create mapping to find id
			slpItems[entry[t][e].id] = e;

		}
	}
}

DrsFile::~DrsFile() {
	for (unsigned int t = 0; t < head.tables; t++) {
		delete entry[t];
	}
	delete entry;
	delete table;
	file.close();
}

int DrsFile::resCount() {
	return table[0].size;
}

Resource *DrsFile::getResource(int index) {
	return getResource(NULL, index);
}

Resource *DrsFile::getResource(Player *p, int index) {
	DrsEntry *selected = &entry[0][index];
	unsigned char *block = new unsigned char[selected->size];
	file.seekg (selected->offset, ios::beg);
	file.read((char *)block, selected->size);
	return new Resource(p, block);
}

Resource *DrsFile::getSlpFromId(Player *p, genie::Graphic *g) {
	DrsEntry *selected = &entry[0][ slpItems[g->SLP] ];
	unsigned char *block = new unsigned char[selected->size];
	file.seekg (selected->offset, ios::beg);
	file.read((char *)block, selected->size);
	return new Resource(p, block, g);
}



} /* namespace std */
