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


namespace std {

class State;
class Instance;
class Type;

class View {
	State *state;	// the state to show in view
	vector<Instance *> obj;

	DrsFile *graph;
	DrsFile *terrain;

	Resource *tile, *tilen;
	Type *arch, *knt, *cannon;
	int view_x, view_y, next_view_x, next_view_y;

	Instance *select;
public:
	View(State *);
	IsoCoord toIso(ScreenCoord);
	ScreenCoord toScreen(IsoCoord);
	void scroll(int, int);
	void click(ScreenCoord, int);
	void draw();
	void test();
	virtual ~View();
};

} /* namespace std */
#endif /* VIEW_H_ */
