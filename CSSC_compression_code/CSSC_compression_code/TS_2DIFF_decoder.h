#pragma once
#include "ByteBuffer.h"
#ifndef __DECODER__
#define __DECODER__
#define ll long long


class TS_2DIFF_decoder {
protected:
	ll count = 0;
	char* deltaBuf;
	int readIntTotalCount = 0;
	int nextReadIndex = 0;
	int packWidth;
	int packNum;
	int encodingLength;

public:
	virtual void readHeader(ByteBuffer buffer) {};
	int dceil(int v);
	bool hasNext(ByteBuffer buffer);

};

#endif