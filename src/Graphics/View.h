/*
 * View.h
 *
 *  Created on: 7/07/2013
 *      Author: asdf
 */

#ifndef VIEW_H_
#define VIEW_H_

#include <vector>

#include "../def.h"
#include "../DrsFile.h"
#include "../Resource.h"
#include "Blendomatic.h"
#include "TileView.h"


namespace std {

class State;
class Instance;
class Type;

class View {
	State *state;	// the state to show in view
	vector<TileView> tiles;

	DrsFile *graph;
	DrsFile *terrain;
	Blendomatic *blend;
	Resource **terrain_type;

	Type *arch, *knt, *cannon, *fireball;
	int next_view_x, next_view_y;

public:
	Instance *select;
	int view_x, view_y;
	ScreenCoord *screen_size;

	View(State *);
	virtual ~View();

	IsoCoord toIso(ScreenCoord);
	ScreenCoord toScreen(IsoCoord);
	void size_ref(ScreenCoord *);
	TileView *getTile(int, int);
	Instance *atPoint(ScreenCoord);
	void scroll(int, int);
	void click(ScreenCoord, int);
	void draw();
	void test();
	void debug();
};

} /* namespace std */
#endif /* VIEW_H_ */
