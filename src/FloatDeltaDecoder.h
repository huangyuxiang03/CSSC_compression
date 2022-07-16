#pragma once

#ifndef __FLOATDELTADECODER__
#define __FLOATDELTADECODER__
#include "IntDeltaDecoder.h"
#include <cstring>

class FloatDeltaDecoder {
private:
	IntDeltaDecoder decoder;
public:
	float convertIntToFloat(int v) {
		float a;
		memcpy(&a, &v, sizeof(float));
		return a;
	}
	float readFloat(ByteBuffer& buffer);
	bool hasNext(ByteBuffer& buffer);
};

#endif // !__FLOATDELTADECODER
