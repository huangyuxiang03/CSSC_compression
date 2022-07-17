#pragma once
#ifndef __INDEXENCODER__
#define __INDEXENCODER__
#include <iostream>
#include "ByteArrayOutputStreamV2.h"

using namespace std;

class IndexEncoder {
private:
	int prevalue;
	int increase_count;
	int* bit_vector0;
	std::uint8_t* bit_vector1_num;
	int bit_vector0_count;
	int bit_vector1_num_count;
	int length;
public:
	IndexEncoder(int length, int preValue) {
		length= length;
		prevalue = preValue;
		increase_count = 0;
		bit_vector0 = new int[length / 200];
		bit_vector1_num = new std::uint8_t[length / 1000];
		bit_vector0_count = 0;
		bit_vector1_num_count = 0;
	}
	void encode_bitvector(ByteArrayOutputStream& out);
	void encode(int num, ByteArrayOutputStream& out);
	void flush(ByteArrayOutputStream& out);
	int getBit_vector1_num_count();
};


#endif // !__INDEXENCODER__