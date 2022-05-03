#pragma once

#ifndef __FLOATDELTAENCODER__
#define __FLOATDELTAENCODER__
#include "IntDeltaEncoder.h"
#include "ByteArrayOutputStream.h"
#include <cstring>

class FloatDeltaEncoder {
private:
	IntDeltaEncoder encoder;
	int convertFloatToInt(float f) {
		int a;
		memcpy(&a, &f, sizeof(int));
		return a;
	}
public:
	void encode(float f, ByteArrayOutputStream& out);
	void flush(ByteArrayOutputStream& out);
};

#endif // !__FLOATDELTAENCODER__
