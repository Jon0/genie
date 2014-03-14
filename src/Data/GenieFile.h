/*
 * GenieFile.h
 *
 *  Created on: 14/03/2014
 *      Author: remnanjona
 */

#ifndef GENIEFILE_H_
#define GENIEFILE_H_

#include <string>
#include <vector>

#include "unit.h"
#include "Buffer.h"

namespace std {

class GenieFile
{

public:
	GenieFile();
	~GenieFile();

	void LoadGenie(const char* filename);
	void SaveGenie(const char* filename);

	bool LoadLanguage(const char* filename);

	void Dump(const char* filename);

	void ReadUnitsData( void ProgressCallback(float, void*), void* CallbackData);

	typedef std::vector<GenieCiv*> CivsType;
	CivsType Civs;
	int VersionNum;

private:
	Buffer *DataBuffer;

	void Decompress(const char* filename);
	void Recompress(const char* filename);

	std::string GenerateName(int id, int lang, const char* name);

};

} /* namespace std */

#endif /* GENIEFILE_H_ */
