/*
 * Minimap.cpp
 *
 *  Created on: 14/03/2014
 *      Author: remnanjona
 */

#include "../Model/Player.h"
#include "../Model/State.h"
#include "../Instance.h"
#include "Dot.h"
#include "Minimap.h"

namespace std {

Minimap::Minimap(State *s) {
	state = s;
	back.width = 400;
	back.height = 200;
	back.anchorx = 200;
	back.anchory = 100;
}

Minimap::~Minimap() {
	// TODO Auto-generated destructor stub
}

void Minimap::generate(int *color) {
	int *image_data = new int[back.width*back.height]();

	for (int i = 0; i < state->getMapSize(); ++i) {
		for (int j = 0; j < state->getMapSize(); ++j) {

			int t = state->getTile(i, j)->type;

			int x = (i + j)*2;
			int y = (i - j) + back.anchory;

			image_data[x + back.width * y] = color[t];
			image_data[x + back.width * y + 1] = color[t];
			image_data[x + back.width * (y+1)] = color[t];
			image_data[x + back.width * (y+1) + 1] = color[t];

		}
	}

	back.createTexture(image_data);
}

ScreenCoord Minimap::toScreen(Tile *) {

}

void Minimap::draw(ScreenCoord *screen_size) {
	drawnAt.x = screen_size->x - 200;
	drawnAt.y = 100;
	back.draw(screen_size->x - 200, 100, -300);

	for (list<Instance>::iterator i = state->allObj.begin(); i != state->allObj.end(); ++i) {

		int ne = (*i).current.ne;
		int se = (*i).current.se;
		int x = (ne + se)*2 + screen_size->x - 400;
		int y = (ne - se) + back.anchory;

		(*i).type->owner->color_dot->draw(x, y, -600);

	}
}

Tile *Minimap::onTile(ScreenCoord sc) {
	IsoCoord i;

	float rx = (sc.x - drawnAt.x + 200) / 4.0;
	float ry = (sc.y - back.anchory) / 2.0;
	i.ne = rx + ry;
	i.se = rx - ry;

	if (0 < i.ne && i.ne < state->getMapSize() && 0 < i.se && i.se < state->getMapSize()) {
		return state->getTile(i);
	}
	return NULL;

}

} /* namespace std */
