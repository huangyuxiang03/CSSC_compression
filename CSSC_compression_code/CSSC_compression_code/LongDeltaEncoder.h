#pragma once
#include "TS_2DIFF_encoder.h"
#define ll long long 

#ifndef __INTDELTAENCODER__
#define __INTDELTAENCODER__

class LongDeltaEncoder : public TS_2DIFF_encoder {
private:
	ll* deltaBlockBuffer;
	ll firstValue;
	ll previousValue;
	ll minDeltaBase;
public:
	~LongDeltaEncoder();
	LongDeltaEncoder(int size);
	LongDeltaEncoder();
	int calculateBitWidthsForDeltaBlockBuffer();
	void calcDelta(ll value);
	void encodeValue(ll value, ByteArrayOutputStream &out);
	void reset();
	int getValueWidth(ll v);
	void writeValueToBytes(int i);
	void calcTwoDiff(int i);
	void writeHeader(ByteArrayOutputStream& out);
	void encode(ll value, ByteArrayOutputStream &out);

};

#endif // !__INTDELTAENCODER__
