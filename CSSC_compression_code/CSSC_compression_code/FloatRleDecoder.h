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
		//float a = ;
		//memcpy(&a, &v, sizeof(float));
		return v / 100000;
	}
	float readFloat(ByteBuffer& buffer);
	bool hasNext(ByteBuffer& buffer);
};

#endif // !__FLOATRLEDECODER__