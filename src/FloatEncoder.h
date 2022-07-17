#pragma once
#include "IntDeltaEncoder.h"
#include "IntRleEncoder.h"
#include "ByteArrayOutputStreamV2.h"

#ifndef __FLOATENCODER__
#define __FLOATENCODER__

class FloatEncoder{
private:
	bool* bitvector;
	IntRleEncoder* exponentEncoder;
	IntRleEncoder* mantissaEncoder;
	int length;
public:
	FloatEncoder(int length) {
		exponentEncoder = new IntRleEncoder();
		mantissaEncoder = new IntRleEncoder();
		bitvector = new bool[length];
	}
	void encode(float f, int pos, ByteArrayOutputStream& out1, ByteArrayOutputStream& out2);
	void flush(ByteArrayOutputStream& out1, ByteArrayOutputStream& out2);
	void encode_bitvector(ByteArrayOutputStream& out3);
	~FloatEncoder() {
		delete exponentEncoder;
		delete mantissaEncoder;
		delete[] bitvector;
	}
};

#endif // !__FLOATENCODER__
