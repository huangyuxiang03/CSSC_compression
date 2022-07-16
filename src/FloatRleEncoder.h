#pragma once
#ifndef __FLOATRLEENCODER__
#define __FLOATRLEENCODER__
#include "IntRleEncoder.h"
#include "ByteArrayOutputStream.h"
#include <cstring>

class FloatRleEncoder {
private:
	IntRleEncoder encoder;
	int convertFloatToInt(float f) {
		int a=0;
		memcpy(&a, &f, sizeof(int));
		return a;
	}
public:
	void encode(float f, ByteArrayOutputStream& out);
	void flush(ByteArrayOutputStream& out);
};

#endif // !__FLOATDELTAENCODER__
