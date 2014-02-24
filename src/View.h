/*
 * View.h
 *
 *  Created on: 7/07/2013
 *      Author: asdf
 */

#ifndef VIEW_H_
#define VIEW_H_

#include <vector>
#include "DrsFile.h"
#include "Resource.h"


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
	int view_x, view_y;

	Instance *select;
public:
	View(State *);
	void scroll(int, int);
	void click(int, int, int);
	void draw();
	void test();
	virtual ~View();
};

} /* namespace std */
#endif /* VIEW_H_ */
