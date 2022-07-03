#include "FloatRleDecoder.h"
/**
 * @brief 
 * 
 * @param buffer 
 * @return float 
 */
float FloatRleDecoder::readFloat(ByteBuffer& buffer)
{
	int ans;
	ans = decoder.readInt(buffer);
	return convertIntToFloat(ans);
}
/**
 * @brief 
 * 
 * @param buffer 
 * @return true 
 * @return false 
 */
bool FloatRleDecoder::hasNext(ByteBuffer& buffer)
{
	return decoder.hasNext(buffer);
}
