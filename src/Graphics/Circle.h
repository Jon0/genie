/*
 * Circle.h
 *
 *  Created on: 28/02/2014
 *      Author: remnanjona
 */

#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "Texture.h"

namespace std {

class Circle: public Texture {
public:
	Circle();
	virtual ~Circle();

	void create(float);
};

} /* namespace std */

#endif /* CIRCLE_H_ */
