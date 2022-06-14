#include "FloatRleEncoder.h"

void FloatRleEncoder::encode(float f, ByteArrayOutputStream& out)
{
	this->encoder.encode(convertFloatToInt(f), out);
}

void FloatRleEncoder::flush(ByteArrayOutputStream& out)
{
	this->encoder.flush(out);
}
