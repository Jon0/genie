/*
 * Projectile.cpp
 *
 *  Created on: 7/03/2014
 *      Author: remnanjona
 */

#include "../DrsFile.h"
#include "../Resource.h"
#include "../Graphics/Frame.h"
#include "Projectile.h"

namespace std {

Projectile::Projectile(Player *p, DrsFile *file, int offset) {
	res = file->getResource(p, offset, true);
}

Projectile::~Projectile() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
