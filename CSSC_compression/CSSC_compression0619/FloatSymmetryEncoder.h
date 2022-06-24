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
    FloatRleEncoder* encoder = new FloatRleEncoder();

   public:
    FloatSymmetryEncoder() {}
    void encode(float num, int pos, ByteArrayOutputStream& out);
    void flush(ByteArrayOutputStream& out);
};

#endif