#pragma once

#include <string>
#include <list>
#include <vector>

#include "Buffer.h"
#include "structs.h"

class GenieUnit {
public:
	genie_unit *u_data;

	Buffer *DataBuffer;
	//LanguageDLL *LangDLL;
	std::string DisplayName;
	int Id;
	int FileOffset;
	int VersionNum;
	typedef std::vector<std::string> SearchablesType;
	SearchablesType Searchables;

	bool operator<(GenieUnit &a) {
		return Id < a.Id;
	}

};

class GenieCiv
{
public:
	std::string Title;

	typedef std::vector<GenieUnit> UnitsType;
	UnitsType Units;

};
