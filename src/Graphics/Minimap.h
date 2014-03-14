/*
 * Minimap.h
 *
 *  Created on: 14/03/2014
 *      Author: remnanjona
 */

#ifndef MINIMAP_H_
#define MINIMAP_H_

#include "../def.h"
#include "Texture.h"

namespace std {

class State;
class Tile;

class Minimap {
	State *state;
	ScreenCoord drawnAt;
public:
	Texture back;
	Minimap(State *);
	virtual ~Minimap();

	void generate(int *);
	ScreenCoord toScreen(Tile *);
	void draw(ScreenCoord *);

	Tile *onTile(ScreenCoord s);
};

} /* namespace std */

#endif /* MINIMAP_H_ */
