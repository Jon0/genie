/*
 * View.h
 *
 *  Created on: 7/07/2013
 *      Author: asdf
 */

#ifndef VIEW_H_
#define VIEW_H_

#include <unordered_set>
#include <vector>

#include "../def.h"
#include "../FileReading/DrsFile.h"
#include "../FileReading/Resource.h"
#include "../GenieData/DatFile.h"
#include "Blendomatic.h"
#include "HealthBar.h"
#include "Minimap.h"
#include "TileView.h"


namespace std {

class Client;
class State;
class Instance;
class Type;

class View {
	State *state;	// the state to show in view
	vector<TileView> tiles;
	Minimap mm;

	DrsFile *graph;
	DrsFile *terrain;
	Blendomatic *blend;
	Resource **terrain_type;

	int next_view_x, next_view_y;
	bool loaded;

public:
	HealthBar hb;
	unordered_set<Instance *> select;


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
	void scrollTo(Tile *);
	void click(ScreenCoord, ScreenCoord, int);
	void drag(ScreenCoord);
	void draw();
	void test();
	void debug();
	void loadGraphics(genie::DatFile *);
};

} /* namespace std */
#endif /* VIEW_H_ */
