/*
 * Data.h
 *
 *  Created on: 15/07/2013
 *      Author: remnanjona
 */

#ifndef DATA_H_
#define DATA_H_

#include <iostream>
#include <fstream>

namespace std {

struct DataHead {
	char version[8];
	short terrains, NumberOfTerrainsUsed;
};

class Data {
	ifstream file;
	int *offsetRestrictions;
public:
	Data();
	virtual ~Data();
};

} /* namespace std */
#endif /* DATA_H_ */
