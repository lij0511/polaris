/*
 * PNGImageDecoder.h
 *
 *  Created on: 2015年12月13日
 *      Author: lijing
 */

#ifndef POLA_PNGIMAGEDECODER_H_
#define POLA_PNGIMAGEDECODER_H_

#include "graphic/image/ImageDecoder.h"

#include <png.h>

namespace pola {
namespace graphic {

class PNGImageDecoder: public ImageDecoder {
public:
	PNGImageDecoder();
	virtual ~PNGImageDecoder();

	virtual Bitmap* decode(io::InputStream* is) override;
};

}
}

#endif /* POLA_PNGIMAGEDECODER_H_ */