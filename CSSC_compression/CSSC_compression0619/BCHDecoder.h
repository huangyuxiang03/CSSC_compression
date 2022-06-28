#pragma once
#include "IntRleDecoder.h"
#include "ByteBuffer.h"

#ifndef __BCHDECODER__
#define __BCHDECODER__

class BCHDecoder {
private:
	IntRleDecoder decoder;
public:
	unsigned long long concatenate(int yyyy, int hhh, int nnn, int www);
	int BCH_63_51(unsigned long long inputString);
	int readInt(int ss, int yyyy, int hhh, int nnn, int www, ByteBuffer& in);
};

#endif // !__BCHDECODER__
