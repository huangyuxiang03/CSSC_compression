#pragma once
#ifndef __INDEXDECODER__
#define __INDEXDECODER__
#include <iostream>
#include "ByteBuffer.h"


using namespace std;

class IndexDecoder {
private:
	int prevalue;
	int increase_count;
	int* bit_vector0;
	std::uint8_t* bit_vector1_num;
	int bit_vector0_count;
	int bit_vector1_num_count;
	int length;
public:
	IndexDecoder(int length, int preValue) {
		length = length;
		prevalue = preValue;
		increase_count = 0;
		bit_vector0 = new int[length / 200];
		bit_vector1_num = new std::uint8_t[length / 1000];
		bit_vector0_count = 0;
		bit_vector1_num_count = 0;
	}
	void setBit_vector0_count(int count);
	void decode_bitvector(ByteBuffer& buffer);
	void readInt(vector<int>& array, ByteBuffer& buffer);
	//void readBit_vector1_num(ByteBuffer& buffer);
	//bool hasNext(ByteBuffer& buffer1, ByteBuffer& buffer2);
};

#endif // !__INDEXDECODER__