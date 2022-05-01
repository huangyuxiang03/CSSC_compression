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
	buffer.get(deltaBuf, encodingLength);
	allocateDataArray();

	previous = firstValue;
	readIntTotalCount = packNum;
	nextReadIndex = 0;
	readPack();
	return firstValue;
}

void LongDeltaDecoder::readPack() {
	for (int i = 0; i < packNum; i++) {
		readValue(i);
		previous = data[i];
	}
}

void LongDeltaDecoder::readHeader(ByteBuffer buffer) {
	minDeltaBase = buffer.readLong();
	firstValue = buffer.readLong();
}

void LongDeltaDecoder::allocateDataArray() {
	delete[] data;
	data = new ll[packNum];
}