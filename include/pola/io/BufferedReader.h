/*
 * BufferedReader.h
 *
 *  Created on: 2016年6月8日
 *      Author: lijing
 */

#ifndef BUFFEREDREADER_H_
#define BUFFEREDREADER_H_

#include "pola/io/Reader.h"
#include "pola/utils/String.h"

namespace pola {
namespace io {

/*
 *
 */
class BufferedReader: public Reader {
public:
	BufferedReader(Reader* reader, size_t bufSize = 1024);
	virtual ~BufferedReader();

	virtual size_t read(void* buffer, size_t size);
	virtual int read();
	virtual size_t skip(size_t size);
	virtual size_t seek(size_t size);
	virtual bool rewind();

	bool readLine(utils::String& line);

	virtual void close();

private:
	int fillBuffer();
	int readChar();
	void chompNewline();
	void maybeSwallowLF();

private:
	Reader* mReader;
	char* mBuffer;
	size_t mBufferSize;

	int32_t mPosition;
	int32_t mEnd;
	bool mLastWasCR;
};

} /* namespace io */
} /* namespace pola */

#endif /* BUFFEREDREADER_H_ */
