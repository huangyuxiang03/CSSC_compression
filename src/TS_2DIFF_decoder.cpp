#include "TS_2DIFF_decoder.h"
#include <cmath>

int TS_2DIFF_decoder::dceil(int v) {
	double ans = ceil(v / 8.0);
	return (int)ans;
}

bool TS_2DIFF_decoder::hasNext(ByteBuffer &buffer) {
	return (nextReadIndex < readIntTotalCount) || buffer.remaining() > 0;
}