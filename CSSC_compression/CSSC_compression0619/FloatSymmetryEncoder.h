#pragma once
#ifndef __SYMMETRYENCODER__
#define __SYMMETRYENCODER__
#include <algorithm>
#include <cmath>
#include <iostream>

#include "ByteArrayOutputStream.h"
#include "FloatDeltaEncoder.h"
#include "FloatRleEncoder.h"

using namespace std;

class FloatSymmetryEncoder {
   private:
    FloatDeltaEncoder* sign_bit_encoder = new FloatDeltaEncoder();
    FloatRleEncoder* exp_encoder = new FloatRleEncoder();
    FloatDeltaEncoder* value_encoder = new FloatDeltaEncoder();

    int currentSignBit = 0;
    int currentExpBit = 0;
    int currentValue = 0;

    int convertFloatToInt(float f) {
        int a = 0;
        memcpy(&a, &f, sizeof(int));
        return a;
    }

   public:
    FloatSymmetryEncoder() {}
    void encode(float num, int pos, ByteArrayOutputStream& out);
    void flush(ByteArrayOutputStream& out);
};

#endif