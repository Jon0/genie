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
#include "Tile.h"
#include "../Types/Type.h"

namespace std {

class Client;
class Instance;

class State {
	int next_id;
public:
	int edge_length, seed;
	vector<Tile> tile;
	vector<Type> types;
	list<Instance> allObj;	// cannot modify sequence
	Client *client;	// TODO remove

	State();
	virtual ~State();

	void startup(int);
	void setClient(Client *);
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
