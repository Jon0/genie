/*
 * Data.cpp
 *
 *  Created on: 15/07/2013
 *      Author: remnanjona
 */

#include "Data.h"

namespace std {

Data::Data() {
	file.open("empires2_x1_p1_out.dat", ios::in | ios::binary);
	file.seekg(0, ios::beg);

	DataHead head;
	file.read((char *)&head, sizeof(DataHead));

	cout << head.version << endl;
	cout << head.terrains << endl;
	cout << head.NumberOfTerrainsUsed << endl;

	offsetRestrictions = new int[head.terrains];
	file.read((char *)offsetRestrictions, head.terrains);

	for (int i = 0; i < head.terrains; ++i) {
		cout << offsetRestrictions[i] << endl;
	}

}

Data::~Data() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
