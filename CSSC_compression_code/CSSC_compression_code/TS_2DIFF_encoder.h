#pragma once

#ifndef __TS_2DIFF__
#define __TS_2DIFF__
#include "ByteArrayOutputStream.h"

class TS_2DIFF_encoder {
protected:
	int BLOCK_DEFAULT_SIZE = 128;
	int blockSize;
	ByteArrayOutputStream out;
	char* encodingBlockBuffer;
	int writeIndex = -1;
	int writeWidth = 0;
public:
	TS_2DIFF_encoder(int size);
	virtual void writeHeader() {};
	virtual void writeValueToBytes(int i) {};
	virtual void calcTwoDiff(int i) {};
	virtual void reset() {};
	virtual int calculateBitWidthsForDeltaBlockBuffer() { return 0; };

	void writeDataWithMinWidth();
	void writeHeaderToBytes();
	void flushBlockBuffer(ByteArrayOutputStream out);
	void flush(ByteArrayOutputStream out);
};

#endif // !__TS_2DIFF__
