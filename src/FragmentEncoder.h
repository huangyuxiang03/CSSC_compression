#pragma once
#ifndef __FRAGMENTENCODER__
#define __FRAGMENTENCODER__
#include <iostream>
#include "FloatDeltaEncoder.h"
#include "ByteArrayOutputStream.h"
#include <cmath>

using namespace std;

class FragmentEncoder {
private:
	float miu;
	float square_miu;
	float sigma;
	//int sigma_count;
	int* fragment_vector;
	int fragment_vector_count;
	float* wait_compress;
	int wait_compress_count;
	FloatDeltaEncoder* encoder;
	int MINFRAGMENTLENGTH;
	int MAXFRAGMENTLENGTH;
	//float* miu_i;
public:
	FragmentEncoder(float miu, int length){//, float* miu_i) {
		MINFRAGMENTLENGTH = 100;
		MAXFRAGMENTLENGTH = 10000;
		reset(miu,length);
		//this->miu_i = miu_i;
	}
	void encode(float num, int pos, ByteArrayOutputStream& out);
	void flush(ByteArrayOutputStream& out);
	void encode_bitvector(ByteArrayOutputStream& out);
	void reset(float miu, int length);
};

#endif // !__FRAGMENTENCODER__