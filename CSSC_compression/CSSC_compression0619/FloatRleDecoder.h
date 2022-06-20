#pragma once
#ifndef __FLOATRLEDECODER__
#define __FLOATRLEDECODER__
#include "IntRleDecoder.h"
#include <cstring>

class FloatRleDecoder {
private:
	IntRleDecoder decoder;
public:
	float convertIntToFloat(int v) {
		float a = 0.0f;
		memcpy(&a, &v, sizeof(float));
		return a;
	}
	float readFloat(ByteBuffer& buffer);
	bool hasNext(ByteBuffer& buffer);
};

#endif // !__FLOATRLEDECODER__