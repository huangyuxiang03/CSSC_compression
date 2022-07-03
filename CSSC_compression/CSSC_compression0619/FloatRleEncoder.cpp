#include "FloatRleEncoder.h"
/**
 * @brief  Encode a float.
 * 
 * @param f  The float to encode.
 * @param out  The output stream.
 */
void FloatRleEncoder::encode(float f, ByteArrayOutputStream& out)
{
	int cft = convertFloatToInt(f);
	this->encoder.encode(cft, out);
}
/**
 * @brief 	Flush the encoder.
 * 
 * @param out  The output stream.
 */
void FloatRleEncoder::flush(ByteArrayOutputStream& out)
{
	this->encoder.flush(out);
}
