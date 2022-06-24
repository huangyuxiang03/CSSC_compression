#pragma once
#ifndef __SYMMETRYENCODER__
#define __SYMMETRYENCODER__
#include <bits/stdc++.h>

#include <cmath>
#include <iostream>

#include "ByteArrayOutputStream.h"
#include "FloatDeltaEncoder.h"
#include "FloatRleEncoder.h"

using namespace std;

class FloatSymmetryEncoder {
   private:
    uint8_t* sign_bit_vector;
    size_t bit_vector_index;
    float miu;  // current mean
    int length = 0;
    float last_value = 0;
    FloatDeltaEncoder* encoder = new FloatDeltaEncoder();

   public:
    FloatSymmetryEncoder(float n_miu, int length) {
        this->length = length / 8 + (length % 8 != 0);

        sign_bit_vector = new uint8_t[this->length];
        memset(sign_bit_vector, 0, this->length * sizeof(*sign_bit_vector));
        this->miu = n_miu;
    }
    void encode(float num, int pos, ByteArrayOutputStream& out);
    void flush(ByteArrayOutputStream& out);
    void encode_bitvector(ByteArrayOutputStream& out);
};

#endif