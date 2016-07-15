/*
 * Texture.h
 *
 *  Created on: 2016年5月19日
 *      Author: lijing
 */

#ifndef POLA_GRAPHIC_TEXTURE_H_
#define POLA_GRAPHIC_TEXTURE_H_

#define MAX_TEXTURE_UNITS_COUNT 3

namespace pola {
namespace graphic {

/*
 *
 */
class Texture {
public:
	Texture() : width(0), height(0){};
	virtual ~Texture() {};

	/**
	 * Width of the backing bitmap.
	 */
	uint32_t width;
	/**
	 * Height of the backing bitmap.
	 */
	uint32_t height;
};

}
}

#endif /* POLA_GRAPHIC_TEXTURE_H_ */
