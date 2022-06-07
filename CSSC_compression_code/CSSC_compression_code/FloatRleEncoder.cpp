#include "FloatRleEncoder.h"

void FloatRleEncoder::encode(float f, ByteArrayOutputStream& out)
{
	encoder.encode(convertFloatToInt(f), out);
}

void FloatRleEncoder::flush(ByteArrayOutputStream& out)
{
	encoder.flush(out);
}
