#pragma once
#include "TS_2DIFF_decoder.h"
#include <corecrt_math.h>

int TS_2DIFF_decoder::ceil(int v) {
	return (int)ceil((double)v / 8.0);
}

bool TS_2DIFF_decoder::hasNext(ByteBuffer buffer) {
	return (nextReadIndex < readIntTotalCount) || buffer.remaining() > 0;
}