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
    FloatDeltaEncoder* encoder = new FloatDeltaEncoder();

   public:
    FloatSymmetryEncoder();
    void encode(float num, int pos, ByteArrayOutputStream& out);
    void flush(ByteArrayOutputStream& out);
};

#endif