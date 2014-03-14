/*
 * GenieFile.cpp
 *
 *  Created on: 14/03/2014
 *      Author: remnanjona
 */

#include <iostream>
#include <sstream>
#include <assert.h>
#include <vector>
#include <time.h>

#include <zlib.h>

#include "structs.h"
#include "GenieFile.h"

namespace std {

const int MAX_GENIESIZE = 8*1024*1024;

GenieFile::GenieFile()
{
	DataBuffer = NULL;
	//LangDLL = new LanguageDLL;
}

GenieFile::~GenieFile()
{
	delete DataBuffer;
	//delete LangDLL;

	for (CivsType::iterator c = Civs.begin(); c != Civs.end(); ++c)
	{
		(*c)->Units.clear();
		delete *c;
	}
}



void GenieFile::LoadGenie(const char* filename)
{
	DataBuffer = new Buffer(MAX_GENIESIZE);

	Decompress(filename);
}

void GenieFile::SaveGenie(const char* filename)
{
	Recompress(filename);
}

#define CHECK_ERROR(e, s) \
	if (e != Z_OK) { \
		std::ostringstream m; \
		m << "Error in " << s << ": " << e; \
		fclose(fh); \
		throw m.str(); \
	}

void GenieFile::Decompress(const char* filename)
{
	FILE *fh = fopen(filename, "rb");
	if (! fh)
		throw "Error opening .dat file";

	int err;
	z_stream d_stream;

	d_stream.zalloc = (alloc_func)0;
	d_stream.zfree = (free_func)0;
	d_stream.opaque = (voidpf)0;

	const int inputBufferSize = 65536;
	char inputBuffer[inputBufferSize];

	d_stream.avail_in = 0;
	d_stream.next_out = (Bytef*) DataBuffer->rawData;
	d_stream.avail_out = DataBuffer->rawBufferSize;

	err = inflateInit2(&d_stream, -MAX_WBITS);
	CHECK_ERROR(err, "inflateInit");

	while (1) {
		if (d_stream.avail_in == 0)
		{
			d_stream.next_in = (Bytef*)inputBuffer;
			d_stream.avail_in = fread(inputBuffer, 1, inputBufferSize, fh);
		}
		if (d_stream.avail_in == 0) break;

		err = inflate(&d_stream, Z_SYNC_FLUSH);
		if (err == Z_STREAM_END) break;
		CHECK_ERROR(err, "inflate");
	}

	DataBuffer->rawBufferSize = d_stream.total_out;
	inflateEnd(&d_stream);

	fclose(fh);
}


void GenieFile::Recompress(const char* filename)
{
	FILE *fh = fopen(filename, "wb");
	if (! fh)
		throw "Error opening .dat file";

	int err;
	z_stream d_stream;

	d_stream.zalloc = (alloc_func)0;
	d_stream.zfree = (free_func)0;
	d_stream.opaque = (voidpf)0;

	const int outputBufferSize = 4096;
	char outputBuffer[outputBufferSize];

	d_stream.next_in = (Bytef*) DataBuffer->rawData;
	d_stream.avail_in = DataBuffer->rawBufferSize;
	d_stream.next_out = (Bytef*) outputBuffer;
	d_stream.avail_out = outputBufferSize;

	err = deflateInit2(&d_stream, Z_DEFAULT_COMPRESSION, Z_DEFLATED, -MAX_WBITS, MAX_MEM_LEVEL, Z_DEFAULT_STRATEGY);
	CHECK_ERROR(err, "deflateInit");

	int flush_type = Z_NO_FLUSH;
	while (1) {
		if (d_stream.avail_in == 0)
			flush_type = Z_FINISH;

		err = deflate(&d_stream, flush_type);

		int count = outputBufferSize - d_stream.avail_out;
		assert(count);
		if (count)
			fwrite(outputBuffer, 1, count, fh);
		if (err == Z_STREAM_END) break;
		CHECK_ERROR(err, "deflate");

		d_stream.avail_out = outputBufferSize;
		d_stream.next_out = (Bytef*) outputBuffer;
	}

	deflateEnd(&d_stream);

	fclose(fh);
}




void GenieFile::Dump(const char* filename)
{
	assert(DataBuffer);
	FILE *fh = fopen(filename, "wb");
	assert(fh);
	fwrite(DataBuffer->rawData, 1, DataBuffer->rawBufferSize, fh);
	fclose(fh);
}


bool GenieFile::LoadLanguage(const char* filename)
{
	//return LangDLL->Open(filename);
}


// Automatically do sizeof type rubbish
#define brds(i) DataBuffer->read(&i, sizeof(i))
// and allocate it too
//#define brdm(i, t) i = new t; DataBuffer->read(i, sizeof(t))
// and handle multiple small types
#define brdl(i, s, t) i = new t[s]; DataBuffer->read(i, s*sizeof(t))


void GenieFile::ReadUnitsData(void ProgressCallback(float, void*) = NULL, void* CallbackData = NULL)
{
	// Some assumptions
	assert(sizeof(char)  == 1);
	assert(sizeof(short) == 2);
	assert(sizeof(int)   == 4);
	assert(sizeof(float) == 4);

	char version[8];
	DataBuffer->seek(0);
	DataBuffer->read(version, 8);

	if (strcmp(version, "VER 5.7") == 0) // AOK X-pack format (no support for non X-pack yet)
		VersionNum = 57;
	else if (strcmp(version, "VER 5.9") == 0) // SWGB + SWGB X-pack format
		VersionNum = 59;
	else
		throw "Invalid version number.";

	// Try to work out where the civ section starts
	int offset = DataBuffer->find("NATURE");
	if (offset < 0)
	{
		offset = DataBuffer->find("Gaia");
		if (offset < 0)
			throw "Can't find NATURE/Gaia!";
	}

	DataBuffer->seek(offset-3);

	short CivCount;
	DataBuffer->read(&CivCount, 2);
	Civs.clear();

	for (int CivNum = 0; CivNum < CivCount; ++CivNum) {
		if (ProgressCallback != NULL)
			ProgressCallback((float)CivNum / (float)CivCount, CallbackData);

		GenieCiv *Civ = new GenieCiv;
		Civ->Units.clear();

		genie_civ *c = new genie_civ;
		brds(c->one);
		brds(c->name1);
		cout << "read civ " << to_string(CivNum) << ", " << c->name1 << endl;
		brds(c->unknown01);
		brds(c->unknown04_length);
		brds(c->unknown02);
		if (VersionNum == 59)
		{
			brds(c->name2);
			brds(c->unknown03);
		}
		brdl(c->unknown04, c->unknown04_length, float);
		brds(c->graphicsset);
		brds(c->unit_count);

		if (VersionNum == 59)
			Civ->Title = c->name2;
		else
			Civ->Title = c->name1;

		bool *UnitExists = new bool[c->unit_count];
		for (int UnitNum = 0; UnitNum < c->unit_count; ++UnitNum)
		{
			int temp;
			brds(temp);
			UnitExists[UnitNum] = temp ? true : false;
		}

		for (int UnitNum = 0; UnitNum < c->unit_count; ++UnitNum)
		{
			if (! UnitExists[UnitNum])
				continue;

			int offset = DataBuffer->tell();

			GenieUnit unit;
			unit.u_data = new genie_unit;
			unit.u_data->Read( DataBuffer, VersionNum );

			assert( unit.u_data->head.id == UnitNum );


			unit.DataBuffer = DataBuffer;
			//unit.LangDLL = LangDLL;
			unit.Id = unit.u_data->head.id;
			unit.VersionNum = VersionNum;
//			unit.Title = GenerateName(unit.Id, u->head.language, u->name1);
			unit.FileOffset = offset;

			unit.Searchables.reserve(4);
			unit.Searchables.push_back(to_string(unit.Id));

			//cout << "unit = " << u->name1 << endl;
			string Name1 = unit.u_data->name1;
			unit.Searchables.push_back(Name1);

			string Name2;
			if (VersionNum == 59)
			{
				Name2 = unit.u_data->name2;
				unit.Searchables.push_back(Name2);
			}
			unit.DisplayName = Name1 + " [" + to_string(unit.Id) + "]";

			Civ->Units.push_back(unit);
		}
		delete[] UnitExists;

		delete c;
		//Civ->Units.sort();
		Civs.push_back(Civ);
	}

}

/*
std::wstring GenieFile::GenerateName(int id, int lang, const char* name)
{
	std::wostringstream Name;
	std::wstring LangText = LangDLL->GetString(lang);
	if (LangText.length() == 0)
		Name << name << " (" << id << ")";
	else
		Name << LangText << " (" << id << ")";
	return Name.str();
}
*/

} /* namespace std */
