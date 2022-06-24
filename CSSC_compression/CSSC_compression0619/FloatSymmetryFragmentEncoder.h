#pragma once
#ifndef __SYMMETRYFRAGMENTENCODER__
#define __SYMMETRYFRAGMENTENCODER__
#include <cmath>
#include <iostream>

#include "ByteArrayOutputStream.h"
#include "FloatDeltaEncoder.h"
#include "FloatRleEncoder.h"

using namespace std;

class FloatSymmetryFragmentEncoder {
   private:
    uint8_t* signed_bit_vector;
    size_t bit_vector_index;
    float miu = 0;  // current mean
    float miu_squared = 0;
    float sigma = 0;  // variance
    int length;
    int signed_bit_vector_length;  // == length / 8 (+ 1)

    int* fragment_vector;
    float* fragment_miu_vector;
    int fragment_vector_count;
    float* wait_compress;
    int wait_compress_count;
    FloatDeltaEncoder* encoder;
    int MINFRAGMENTLENGTH;
    int MAXFRAGMENTLENGTH;

    int div_ceil(int a, int b) {
        return a / b + (a % b != 0);
    }

    int bitwiseFloatToInt(float f) {
        int a;
        memcpy(&a, &f, sizeof(int));
        return a;
    }

   public:
    FloatSymmetryFragmentEncoder(int length) {
        this->length = length;
        this->signed_bit_vector_length = div_ceil(length, 8);

        signed_bit_vector = new uint8_t[this->length];
        memset(signed_bit_vector, 0, this->length * sizeof(*signed_bit_vector));

        MINFRAGMENTLENGTH = 100;
        MAXFRAGMENTLENGTH = 10000;

        fragment_vector = new int[div_ceil(length, MINFRAGMENTLENGTH)];
        fragment_miu_vector = new float[div_ceil(length, MINFRAGMENTLENGTH)];
        wait_compress = new float[MAXFRAGMENTLENGTH];
        fragment_vector_count = 0;
        wait_compress_count = 0;
        encoder = new FloatDeltaEncoder();
    }
    void encode(float num, int pos, ByteArrayOutputStream& out);
    void flush(ByteArrayOutputStream& out);
    void encode_bitvector(ByteArrayOutputStream& out);
};

#endif