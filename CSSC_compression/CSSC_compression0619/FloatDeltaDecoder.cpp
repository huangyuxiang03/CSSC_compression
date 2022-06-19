#pragma once
#include "FloatDeltaDecoder.h"

float FloatDeltaDecoder::readFloat(ByteBuffer& buffer) {
	int ans;// = decoder.readInt(buffer);
	ans = decoder.readInt(buffer);
	return convertIntToFloat(ans);
}

bool FloatDeltaDecoder::hasNext(ByteBuffer& buffer) {
	return decoder.hasNext(buffer);
}