/*
 * State.h
 *
 *  Created on: 9/07/2013
 *      Author: asdf
 */

#ifndef STATE_H_
#define STATE_H_

#include <vector>
#include <list>

#include "../def.h"
#include "../GenieData/DatFile.h"
#include "Types/Type.h"
#include "Player.h"
#include "Tile.h"

namespace std {

class Client;
class Instance;

class State {
	int next_id;
public:
	genie::DatFile *gamedata;
	int edge_length, seed;
	vector<Tile> tile;
	vector<Type> types;
	list<Instance> allObj;	// cannot modify sequence
	vector<Player> players;
	Client *client;	// TODO remove

	State(genie::DatFile *);
	virtual ~State();

	void startup(int);
	void setClient(Client *);
	bool withinMap(IsoCoord);
	void update();
	void addObj(Instance);
	Tile *getTile(int, int);
	Tile *getTile(IsoCoord);
	Tile *getTile(Pointi);
	int getMapSize();
	int getNextID();

	void issueCommand(Instance *, Instance *);
	void issueCommand(Instance *, IsoCoord);
	Instance *fromID(int);
};

} /* namespace std */
#endif /* STATE_H_ */
