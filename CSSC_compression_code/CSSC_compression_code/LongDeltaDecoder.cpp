#pragma once
#include "LongDeltaDecoder.h"

ll LongDeltaDecoder::readT(ByteBuffer buffer) {
	if (nextReadIndex == readIntTotalCount) {
		return loadIntBatch(buffer);
	}
	return data[nextReadIndex++];
}

ll LongDeltaDecoder::loadIntBatch(ByteBuffer buffer) {
	packNum = buffer.readInt();
	packWidth = buffer.readInt();
	count++;
	readHeader(buffer);

	encodingLength = ceil(packNum * packWidth);
	deltaBuf = new char[encodingLength];
	buffer.get(deltaBuf);

}