#pragma once

// For unknowns:
typedef unsigned char raw;

#include "unitparts.h"

#include "Buffer.h"

class genie_civ {
public:

	genie_civ();
	~genie_civ();

	char	one;
	char	name1[16];
	short	unknown01[2];
	short	unknown04_length;
	short	unknown02[2];
	char	name2[20];
	short	unknown03[4];
	float*	unknown04;
	char	graphicsset;
	short	unit_count;

};

class genie_unit {
public:
	genie_unit();
	~genie_unit();

	void Read(Buffer *DataBuffer, int VersionNum);
	void Write(Buffer *DataBuffer, int VersionNum);

	char	type;

	genie_unit_head head;

	char	unknown01_length;
	raw*	unknown01; // x 4*unknown01_length

	short	sounds[3];
	char*	name1; // x head.name1_length
	short	name2_length;
	char*	name2;
	short	unitline_id;
	char	mintechlevel;
	short	id2;
	short	id3;

	genie_unit_part2*	part2;
	genie_unit_part3*	part3;
	genie_unit_part4*	part4;
	genie_unit_part5*	part5;

	short	attacks_length;
	short*	attacks; // x 2*attacks_length
	short	armour_length;
	short*	armour; // x 2*armour_length

	genie_unit_part6*	part6;
	genie_unit_part7*	part7;
	genie_unit_part8*	part8;
	genie_unit_part9*	part9;
	genie_unit_part10*	part10;
	genie_unit_part11*	part11;
	genie_unit_part12*	part12;
	genie_unit_part14*	part14;
	genie_unit_part15*	part15;

};
