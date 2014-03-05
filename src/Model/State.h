/*
 * State.h
 *
 *  Created on: 9/07/2013
 *      Author: asdf
 */

#ifndef STATE_H_
#define STATE_H_

#include <map>
#include <iostream>

#include "../def.h"
#include "../Instance.h"
#include "Tile.h"

namespace std {

class Instance;

class State {
	int edge_length;
	vector<Tile> tile;
	vector<Instance *> allObj;
public:
	State() {
		edge_length = 100;

		/* produce tile array */
		for (int y = 0; y < edge_length; ++y) {
			for (int x = 0; x < edge_length; ++x) {
				tile.push_back(*new Tile(x, y));
			}
		}

		/* random terrain generation */
		for (int i = 0; i < 50; ++i) {
			int x_pos = rand() % edge_length;
			int y_pos = rand() % edge_length;
			int size = rand() % 50;
			int type = rand() % 18;
			for (int y = y_pos; 0 <= y && y < edge_length && y < y_pos + size;
					++y) {
				for (int x = x_pos;
						0 <= x && x < edge_length && x < x_pos + size; ++x) {
					getTile(x, y)->type = type;
				}
			}
		}

		/* adjacent tile connections */
		for (int y = 0; y < edge_length - 1; ++y) {
			for (int x = 0; x < edge_length - 1; ++x) {
				getTile(x, y)->connect(0, getTile(x + 1, y));
				getTile(x, y + 1)->connect(1, getTile(x, y));
				getTile(x + 1, y)->connect(2, getTile(x, y));
				getTile(x, y)->connect(3, getTile(x, y + 1));
			}
		}
	}

	~State() {}

	void update() {
		for (unsigned int i = 0; i < allObj.size(); ++i) {
			allObj.data()[i]->update();
		}
	}

	void addObj(Instance *obj) {
		allObj.push_back(obj);
		getTile( obj->getIso() )->addObj(obj);
	}

	Tile *getTile(int x, int y) {
		return &tile.data()[y * edge_length + x];
	}

	Tile *getTile(IsoCoord ic) {
		return getTile(ic.ne, ic.se);
	}

	Tile *getTile(Pointi p) {
		return getTile(p.x, p.y);
	}

	int getMapSize() {
		return edge_length;
	}

};

} /* namespace std */
#endif /* STATE_H_ */
