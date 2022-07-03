#pragma once
#include "FloatDeltaDecoder.h"
/**
 * @brief  read float from buffer
 * 
 * @param buffer 
 * @return float 
 */
float FloatDeltaDecoder::readFloat(ByteBuffer& buffer) { 
	int ans;// = decoder.readInt(buffer);
	ans = decoder.readInt(buffer);
	return convertIntToFloat(ans);
}
/**
 * @brief check if there is next element in buffer
 * 
 * @param buffer 
 * @return true 
 * @return false 
 */
bool FloatDeltaDecoder::hasNext(ByteBuffer& buffer) {
	return decoder.hasNext(buffer);
}