#pragma once
#include "ByteBuffer.h"
#include "TS_2DIFF_decoder.h"
#ifndef __LONGDELTADECODER__
#define __LONGDELTADECODER__
#define ll long long

class LongDeltaDecoder : public TS_2DIFF_decoder{
private:
	ll firstValue;
	ll* data;
	ll previous;
	ll minDeltaBase;
public:
	ll readT(ByteBuffer buffer);
	ll loadIntBatch(ByteBuffer buffer);
	void readPack();
	ll readLong(ByteBuffer buffer);
	void readHeader(ByteBuffer buffer);
	void allocateDataArray();
	void readValue(int i);
	void reset() { }
};

#endif // !__LONGDELTADECODER__
