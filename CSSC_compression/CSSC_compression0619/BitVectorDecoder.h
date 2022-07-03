#pragma once
#ifndef __BITVECTORDECODER__
#define __BITVECTORDECODER__
#include <iostream>
#include "IntDeltaDecoder.h"
#include "ByteBuffer.h"


using namespace std;

class BitVectorDecoder {
private:
	IntDeltaDecoder* decoder1;
	IntDeltaDecoder* decoder2;
	int* bit_vector;			//!< bit vector
	int mid;					//!< mid of bit vector
	int length;					//!< length of bit vector
public:
	BitVectorDecoder(int length, int middle) {
		decoder1 = new IntDeltaDecoder();
		decoder2 = new IntDeltaDecoder();
		this->length = length;
		bit_vector = new int[length];
		mid = middle;
	}
	void decode_bitvector(ByteBuffer& buffer);
	int readInt(int j, ByteBuffer& buffer1, ByteBuffer& buffer2);
	bool hasNext(ByteBuffer& buffer1, ByteBuffer& buffer2);

	~BitVectorDecoder() {
		delete decoder1;
		delete decoder2;
		delete[] bit_vector;
	}
};




#endif // !__BITVECTORDECODER__