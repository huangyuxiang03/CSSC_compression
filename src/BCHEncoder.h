#pragma once
#include "IntRleEncoder.h"

#ifndef __BCHENCODER__
#define __BCHENCODER__

class BCHEncoder {
private:
	IntRleEncoder encoder;
public:
	unsigned long long concatenate(int yyyy, int hhh, int nnn, int www);
	int BCH_63_51(unsigned long long inputString);
	void encode(int num, int ss, int yyyy, int hhh, int nnn, int www, ByteArrayOutputStream& out);
	void flush(ByteArrayOutputStream& out);
};

#endif // !__BCHENCODER__