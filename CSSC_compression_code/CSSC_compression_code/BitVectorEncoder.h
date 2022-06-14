#pragma once
#ifndef __BITVECTORENCODER__
#define __BITVECTORENCODER__
#include <iostream>
#include "IntDeltaEncoder.h"
#include "ByteArrayOutputStream.h"

using namespace std;

class BitVectorEncoder {
private:
	IntDeltaEncoder* encoder1;
	IntDeltaEncoder* encoder2;
	int* bit_vector;
	int mid;
	int length;
public:
	BitVectorEncoder(int length,int middle) {
		encoder1 = new IntDeltaEncoder();
		encoder2 = new IntDeltaEncoder();
		this->length = length;
		bit_vector = new int[length];
		mid = middle;
	}
	void encode(int num, int pos, ByteArrayOutputStream& out1, ByteArrayOutputStream& out2);
	void flush(ByteArrayOutputStream& out1, ByteArrayOutputStream& out2);
	void encode_bitvector(ByteArrayOutputStream& out3);
};

#endif // !__BITVECTORENCODER__