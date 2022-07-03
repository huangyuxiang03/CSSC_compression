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
	float miu;     				//!< miu of the encoder.
	float square_miu;			//!< square of the miu of the encoder.
	float sigma;				//!< sigma of the encoder.
	//int sigma_count;			//!< count of the sigma of the encoder.
	int* fragment_vector;		//!< fragment vector of the encoder.
	int fragment_vector_count;	//!< count of the fragment vector of the encoder.
	float* wait_compress;		//!< wait compress of the encoder.
	int wait_compress_count;	//!< count of the wait compress of the encoder.
	FloatDeltaEncoder* encoder;	//!< encoder of float delta.
	int MINFRAGMENTLENGTH;		//!< minimum length of the fragment.
	int MAXFRAGMENTLENGTH;		//!< maximum length of the fragment.
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