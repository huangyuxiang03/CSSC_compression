#include "FloatRleDecoder.h"

float FloatRleDecoder::readFloat(ByteBuffer& buffer)
{
	int ans;
	ans = decoder.readInt(buffer);
	return convertIntToFloat(ans);
}

bool FloatRleDecoder::hasNext(ByteBuffer& buffer)
{
	return decoder.hasNext(buffer);
}
