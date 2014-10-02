/*
 * Path.cpp
 *
 *  Created on: 26/07/2013
 *      Author: asdf
 */

#include <stdlib.h>
#include <unordered_set>
#include <queue>
#include <map>
#include <iostream>

#include "State.h"
#include "Path.h"

namespace std {

Path::Path(Tile *start, IsoCoord *t) {
	target = t;
	search(start, target);
}

Path::Path(State *s, IsoCoord *a, IsoCoord *b):
		Path(s->getTile(a->ne, a->se), b) {}

Path::~Path() {
	// TODO Auto-generated destructor stub
}

int Path::length() {
	return point.size() - 1;
}

Tile *Path::next() {
	point.pop();
	return point.front();
}

void Path::search(Tile *start, IsoCoord *t) {
	unordered_set<Tile *> cset; // The set of nodes already evaluated.

	// The set of tentative nodes to be evaluated, initially containing the start node
	unordered_set<Tile *> oset_tiles;
	priority_queue<PathNode, vector<PathNode>, CostComparator> oset;

	// The map of navigated nodes.
	map<Tile *, Tile *> from;
	from.insert ( std::pair<Tile *, Tile *>(start, NULL) );	// ensure start has no from

	// start node
	PathNode s;
	s.tile = start;
	s.gcost = 0.0f;
	s.fcost = s.tile->dist(*t); // heuristic_cost_estimate(start, goal)
	oset.push(s);

	// while openset is not empty
	while (!oset.empty()) {

		//current := the node in openset having the lowest f_score[] value
		PathNode current = oset.top();

		// set final path
		if ( current.tile->contains( *t ) ) {
			vector<Tile *> stack;
			Tile *tile_from = current.tile;

			while (tile_from) {
				stack.push_back(tile_from);
				tile_from = from[tile_from];
			}
			while (!stack.empty()) {
				point.push( stack.back() );
				stack.pop_back();
			}
			return;
		}

		// remove current from openset
		oset.pop();
		oset_tiles.erase(current.tile);

		// add current to closedset
		cset.insert(current.tile);

		// for each neighbor in neighbor_nodes(current)
		for (int n = 0; n < 8; ++n) {
			Tile *neighbor = NULL;
			if (n < 4) neighbor = current.tile->getAdj(n);

			// for all diagonal neighbors
			else {
				neighbor = current.tile->getAdj(n % 4)->getAdj((n+1) % 4);
			}
			if (!neighbor || cset.count(neighbor) > 0 || !neighbor->isPassable()) continue;

			// tentative_g_score := g_score[current] + dist_between(current,neighbor)
			float sum = current.gcost + current.tile->dist(neighbor->position);

			// if neighbor not in openset or tentative_g_score < g_score[neighbor]
			if ( oset_tiles.count(neighbor) == 0 ) {
				from.insert ( std::pair<Tile *, Tile *>(neighbor, current.tile) );

				PathNode neighbor_node;
				neighbor_node.tile = neighbor;
				neighbor_node.gcost = sum;
				neighbor_node.fcost = sum + neighbor->dist(*t); //+ heuristic_cost_estimate(neighbor, goal)

                //if neighbor not in openset
				oset.push(neighbor_node);
				oset_tiles.insert(neighbor);
			}
		}
	}

	cout << "could not find path" << endl;
	return;

}

} /* namespace std */
