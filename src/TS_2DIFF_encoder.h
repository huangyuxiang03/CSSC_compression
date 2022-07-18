#pragma once

#ifndef __TS_2DIFF__
#define __TS_2DIFF__
#include "ByteArrayOutputStreamV2.h"
#include <iostream>

class TS_2DIFF_encoder {
protected:
	static int BLOCK_DEFAULT_SIZE;
	int blockSize;
	char* encodingBlockBuffer;
	int writeIndex = -1;
	int writeWidth = 0;
	time_t flush_beg;
	time_t flush_end;
	time_t flush_time = 0;
public:
	TS_2DIFF_encoder(int size);
	TS_2DIFF_encoder() : TS_2DIFF_encoder(BLOCK_DEFAULT_SIZE) { }
	virtual void writeHeader(ByteArrayOutputStream& out) {};
	virtual void writeValueToBytes(int i) {};
	virtual void calcTwoDiff(int i) {};
	virtual void reset() {};
	virtual int calculateBitWidthsForDeltaBlockBuffer() { return 0; };

	void writeDataWithMinWidth(ByteArrayOutputStream &out);
	void writeHeaderToBytes(ByteArrayOutputStream &out);
	void flushBlockBuffer(ByteArrayOutputStream &out);
	void flush(ByteArrayOutputStream &out);
};


#endif // !__TS_2DIFF__
