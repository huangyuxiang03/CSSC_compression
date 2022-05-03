#pragma once
#include "ByteBuffer.h"
#include "TS_2DIFF_decoder.h"
#ifndef __INTLONGDELTADECODER__
#define __INTLONGDELTADECODER__
#define ll long long

class IntDeltaDecoder : public TS_2DIFF_decoder {
private:
	int firstValue;
	int* data;
	int previous;
	int minDeltaBase;
	bool dataArrayAllocated = false;
public:
	int readT(ByteBuffer& buffer);
	int loadIntBatch(ByteBuffer& buffer);
	void readPack();
	int readInt(ByteBuffer& buffer);
	void readHeader(ByteBuffer& buffer);
	void allocateDataArray();
	void readValue(int i);
	void reset() { }
	~IntDeltaDecoder();
};

#endif // !__LONGDELTADECODER__
