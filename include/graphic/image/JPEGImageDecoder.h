/*
 * JPEGImageDecoder.h
 *
 *  Created on: 2015年12月30日
 *      Author: lijing
 */

#ifndef POLA_JPEGIMAGEDECODER_H_
#define POLA_JPEGIMAGEDECODER_H_

#include "graphic/image/ImageDecoder.h"

#include <stdio.h>
extern "C" {
    #include "jpeglib.h"
    #include "jerror.h"
}
#include <setjmp.h>

namespace pola {
namespace graphic {

struct pola_jpeg_source_mgr : jpeg_source_mgr {
	pola_jpeg_source_mgr(io::InputStream* is);
	~pola_jpeg_source_mgr();

	// fStream is ref'ed and unref'ed
	io::InputStream*       fStream;
	enum {
		kBufferSize = /*TODO 有些jpg解析汇报异常(Miscellaneous marker 0xe1, length 14952) Why?              1024*/1024 * 500
	};
	char    fBuffer[kBufferSize];
};
/* Our error-handling struct.
 *
*/
struct pola_jpeg_error_mgr : jpeg_error_mgr {
    jmp_buf fJmpBuf;
};

class JPEGImageDecoder: public ImageDecoder {
public:
	JPEGImageDecoder();
	virtual ~JPEGImageDecoder();

	virtual Bitmap* decode(io::InputStream* is, Bitmap::Format format = Bitmap::UNKONWN) override;
};

}
}

#endif /* POLA_JPEGIMAGEDECODER_H_ */