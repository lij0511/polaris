/*
 * BitmapUtils.h
 *
 *  Created on: 2016年7月27日
 *      Author: lijing
 */

#ifndef POLA_BITMAPUTILS_H_
#define POLA_BITMAPUTILS_H_

#include "pola/graphic/Image.h"
#include "pola/graphic/Color.h"

namespace pola {
namespace graphic {

bool clearBitmap(Image& bitmap, uint32_t color);

enum BitmapScaleMode {
	NEAREST,
	BILINEAR,
};

bool scaleBitmap(const Image& src, Image*& dst, float scaleW, float scaleH, BitmapScaleMode scaleMode = BILINEAR);

uint32_t convertColorFormat(uint32_t srcColor, PixelFormat srcFormat, PixelFormat dstFormat);

} /* namespace graphic */
} /* namespace pola */

#endif /* POLA_BITMAPUTILS_H_ */
