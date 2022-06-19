#pragma once
#include "TS_2DIFF_encoder.h"
#define ll long long 

#ifndef __INT32DELTAENCODER__
#define __INT32DELTAENCODER__

class IntDeltaEncoder : public TS_2DIFF_encoder {
private:
	int* deltaBlockBuffer;
	int firstValue;
	int previousValue;
	int minDeltaBase;
public:
	~IntDeltaEncoder();
	IntDeltaEncoder(int size);
	IntDeltaEncoder();
	int calculateBitWidthsForDeltaBlockBuffer();
	void calcDelta(int value);
	void encodeValue(int value, ByteArrayOutputStream& out);
	void reset();
	int getValueWidth(int v);
	void writeValueToBytes(int i);
	void calcTwoDiff(int i);
	void writeHeader(ByteArrayOutputStream& out);
	void encode(int value, ByteArrayOutputStream& out);

};

#endif // !__INT32DELTAENCODER__
