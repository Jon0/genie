/*
 * TileView.h
 *
 *  Created on: 6/03/2014
 *      Author: remnanjona
 */

#ifndef TILEVIEW_H_
#define TILEVIEW_H_

#include "../def.h"

namespace std {

class Blendomatic;
class Instance;
class Texture;
class Resource;
class Tile;
class View;

class TileView {
	int tile_x, tile_y; // where the tile was last drawn
public:
	Tile *tile;
	Texture *image;

	TileView(Tile *, Resource **, Blendomatic *);
	virtual ~TileView();

	bool onScreen(View *);
	void draw(View *);
	Instance *select(View *, ScreenCoord);
};

} /* namespace std */

#endif /* TILEVIEW_H_ */
