/*
 * TileView.cpp
 *
 *  Created on: 6/03/2014
 *      Author: remnanjona
 */

#include "TileView.h"

#include "../Graphics/Frame.h"
#include "../Model/Tile.h"
#include "../Model/Types/Type.h"
#include "../Model/Instance.h"
#include "../FileReading/Resource.h"
#include "Blend.h"
#include "Blendomatic.h"
#include "View.h"

namespace std {

TileView::TileView(Tile *t, Resource **terrain_type, Blendomatic *blend) {
	tile = t;

	int ne = tile->x;
	int se = tile->y;


	Frame *a = terrain_type[tile->type]->getFrame((ne % 10) + (se % 10) * 10);
	Blend *tile_blend = new Blend(a);

	// for each direction
	for (int i = 0; i < 4; ++i) {
		Tile *n = tile->getAdj(i);

		// neighbor is dominant
		if (n && n->type > tile->type) {
			Frame *b = terrain_type[n->type]->getFrame((ne % 10) + (se % 10) * 10);
			tile_blend->mix(b, blend->getAngle(i));
		}
	}

	tile_blend->makeTexture();
	image = tile_blend;
}

TileView::~TileView() {

}

bool TileView::onScreen(View *v) {
	int ne = tile->x;
	int se = tile->y;

	/* update tile position */
	tile_x = v->view_x+(se+ne)*48;
	tile_y = v->view_y+(ne-se)*24;

	return -96 <= tile_x && tile_x < v->screen_size->x && 0 <= tile_y && tile_y < v->screen_size->y + 96;
}

void TileView::draw(View *v) {
	if ( onScreen(v) ) {
		image->draw(tile_x, tile_y, 48);

		// draw all objects on the tile
		for (int i = 0; i < tile->objs(); ++i) {
			Instance *obj = tile->getObj(i);
			ScreenCoord sc = v->toScreen(obj->getIso());
			obj->draw(sc);

			if (v->select.count(obj) > 0) {
				obj->type->circle.draw(sc.x, sc.y, 0);

				sc.y += 60;

				float percent = (float)obj->hp / (float)obj->type->unit->HitPoints;
				v->hb.draw(sc, percent);
			}
		}
	}
}

Instance *TileView::select(View *v, ScreenCoord click) {
	for (int i = 0; i < tile->objs(); ++i) {
		Instance *obj = tile->getObj(i);
		ScreenCoord sc = v->toScreen(obj->getIso()); // point anchor is drawn to
		sc.x = click.x - sc.x;
		sc.y = click.y - sc.y; // get point relative to anchor
		if (obj->pointCheck(sc)) return obj;
	}

	// need to check adjacent tiles too
	for (int a = 0; a < 4; ++a) {
		Tile *t = tile->getAdj(a);
		if (t) {
			for (int i = 0; i < t->objs(); ++i) {
				Instance *obj = t->getObj(i);
				ScreenCoord sc = v->toScreen(obj->getIso());
				sc.x = click.x - sc.x;
				sc.y = click.y - sc.y;
				if (obj->pointCheck(sc)) return obj;
			}
		}
	}
	return NULL; // nothing found
}

} /* namespace std */
