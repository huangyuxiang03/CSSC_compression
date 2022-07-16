#include "FloatRleEncoder.h"

void FloatRleEncoder::encode(float f, ByteArrayOutputStream& out)
{
	int cft = convertFloatToInt(f);
	this->encoder.encode(cft, out);
}

void FloatRleEncoder::flush(ByteArrayOutputStream& out)
{
	this->encoder.flush(out);
}
