/*
 * Projectile.h
 *
 *  Created on: 7/03/2014
 *      Author: remnanjona
 */

#ifndef PROJECTILE_H_
#define PROJECTILE_H_

namespace std {

class Player;

class Projectile {
public:
	Resource *res;
	Projectile(Player *, DrsFile *, int);
	virtual ~Projectile();
};

} /* namespace std */

#endif /* PROJECTILE_H_ */
