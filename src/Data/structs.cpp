#include <iostream>
#include <assert.h>

#include "structs.h"

genie_civ::genie_civ() {
	unknown04 = NULL;
}
genie_civ::~genie_civ() {
	delete[] unknown04;
}


genie_unit::genie_unit()
{
	unknown01 = NULL;
	name1 = NULL;
	name2 = NULL;

	part2 = NULL;	part3 = NULL;	part4 = NULL;	part5 = NULL;
	part6 = NULL;	part7 = NULL;	part8 = NULL;	part9 = NULL;
	part10 = NULL;	part11 = NULL;	part12 = NULL;	part14 = NULL;
	part15 = NULL;

	attacks = NULL;
	armour = NULL;
}

genie_unit::~genie_unit()
{
	// I like garbage collection.

	delete[] unknown01;
	delete[] name1;
	delete[] name2;

	delete[] part2;		delete[] part3;		delete[] part4;
	delete[] part5;		delete[] part6;		delete[] part7;
	delete[] part8;		delete[] part9;		delete[] part10;
	delete[] part11;	delete[] part12;	delete[] part14;
	delete[] part15;

	delete[] attacks;
	delete[] armour;
}



// Automatically do sizeof type rubbish
#define brds(i) DataBuffer->read(&i, sizeof(i))
// and allocate it too
#define brdm(i, t) i = new t; DataBuffer->read(i, sizeof(t))
// and handle multiple small types
#define brdl(i, s, t) i = new t[s]; DataBuffer->read(i, s*sizeof(t))


void genie_unit::Read(Buffer *DataBuffer, int VersionNum)
{
	brds(type);
	brds(head);
	brds(unknown01_length);
	if (unknown01_length < 0 || unknown01_length > 32767) // an arbitrary big number, to avoid allocating several gigabytes of RAM
		throw "Unrecognised .dat format";
	brdl(unknown01, 5*unknown01_length, raw);

	brds(sounds);
	if (head.name1_length)
	{
		brdl(name1, head.name1_length, char);
	}
	else
	{
		name1 = new char[1];
		name1[0] = 0;
	}

	if (VersionNum == 59)
	{
		brds(name2_length);
		if (name2_length)
		{
			brdl(name2, name2_length, char);
		}
		else
		{
			name2 = new char[1];
			name2[0] = 0;
		}

		brds(unitline_id);
		brds(mintechlevel);
	}
	brds(id2);
	brds(id3);

	if (type != 10)
	{
		brdm(part2, genie_unit_part2);
	}
	switch (type)
	{
		case 30:
			brdm(part4, genie_unit_part4);
			break;
		case 60:
			brdm(part6, genie_unit_part6);
			brdm(part5, genie_unit_part5);
			brds(attacks_length);
			brdl(attacks, 2*attacks_length, short);
			brds(armour_length);
			brdl(armour, 2*armour_length, short);
			brdm(part9, genie_unit_part9);
			break;
		case 70:
			brdm(part3, genie_unit_part3);
			brdm(part5, genie_unit_part5);
			brds(attacks_length);
			brdl(attacks, 2*attacks_length, short);
			brds(armour_length);
			brdl(armour, 2*armour_length, short);
			//brdm(part7, genie_unit_part7);
			brdm(part10, genie_unit_part10);
			//brdm(part12, genie_unit_part12);
			brdm(part14, genie_unit_part14);
			break;
		case 80:
			brdm(part3, genie_unit_part3);
			brdm(part5, genie_unit_part5);
			brds(attacks_length);
			brdl(attacks, 2*attacks_length, short);
			brds(armour_length);
			brdl(armour, 2*armour_length, short);
			brdm(part8, genie_unit_part8);
			brdm(part11, genie_unit_part11);
			brdm(part12, genie_unit_part12);
			brdm(part15, genie_unit_part15);
			break;
	}

	assert(head.languageplus1000 == head.language+1000);

	assert(head.zero_00 == 0);
	assert(head.zero_01 == 0);
	assert(head.minus1_01 == -1);
	assert(head.minus1_02 == -1);

}

// Equivalent macros for writing
#define bwrs(i) DataBuffer->write(&i, sizeof(i))
#define bwrm(i, t) DataBuffer->write(i, sizeof(t))
#define bwrl(i, s, t) DataBuffer->write(i, s*sizeof(t))


// Code duplication is bad. There must be a nicer way to do this...

void genie_unit::Write(Buffer *DataBuffer, int VersionNum)
{
	bwrs(type);

	bwrs(head);

	bwrs(unknown01_length);
	bwrl(unknown01, 5*unknown01_length, raw);

	bwrs(sounds);

	if (head.name1_length)
	{
		bwrl(name1, head.name1_length, char);
	}

	if (VersionNum == 59)
	{
		bwrs(name2_length);
		if (name2_length)
		{
			bwrl(name2, name2_length, char);
		}

		bwrs(unitline_id);
		bwrs(mintechlevel);
	}

	bwrs(id2);
	bwrs(id3);

	if (type != 10) {
		bwrm(part2, genie_unit_part2);
	}

	switch (type) {
		case 30:
			bwrm(part4, genie_unit_part4);
			break;
		case 60:
			bwrm(part6, genie_unit_part6);
			bwrm(part5, genie_unit_part5);
			bwrs(attacks_length);
			bwrl(attacks, 2*attacks_length, short);
			bwrs(armour_length);
			bwrl(armour, 2*armour_length, short);
			bwrm(part9, genie_unit_part9);
			break;
		case 70:
			bwrm(part3, genie_unit_part3);
			bwrm(part5, genie_unit_part5);
			bwrs(attacks_length);
			bwrl(attacks, 2*attacks_length, short);
			bwrs(armour_length);
			bwrl(armour, 2*armour_length, short);
			bwrm(part7, genie_unit_part7);
			bwrm(part10, genie_unit_part10);
			bwrm(part12, genie_unit_part12);
			bwrm(part14, genie_unit_part14);
			break;
		case 80:
			bwrm(part3, genie_unit_part3);
			bwrm(part5, genie_unit_part5);
			bwrs(attacks_length);
			bwrl(attacks, 2*attacks_length, short);
			bwrs(armour_length);
			bwrl(armour, 2*armour_length, short);
			bwrm(part8, genie_unit_part8);
			bwrm(part11, genie_unit_part11);
			bwrm(part12, genie_unit_part12);
			bwrm(part15, genie_unit_part15);
			break;
	}
}
