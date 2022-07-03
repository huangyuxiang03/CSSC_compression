#pragma once
#include "LongDeltaDecoder.h"
/**
 * @brief 
 * 
 * @param buffer 
 * @return ll 
 */
ll LongDeltaDecoder::readT(ByteBuffer& buffer) {
	if (nextReadIndex == readIntTotalCount) {
		return loadIntBatch(buffer);
	}
	return data[nextReadIndex++];
}
/**
 * @brief 
 * 
 * @param buffer 
 * @return ll 
 */
ll LongDeltaDecoder::loadIntBatch(ByteBuffer& buffer) {
	packNum = buffer.readInt();
	packWidth = buffer.readInt();
	count++;
	readHeader(buffer);

	encodingLength = dceil(packNum * packWidth);
	if (deltaBufAllocated)
		delete[] deltaBuf;
	deltaBuf = new char[encodingLength];
	deltaBufAllocated = true;
	buffer.get(deltaBuf, encodingLength);
	allocateDataArray();

	previous = firstValue;
	readIntTotalCount = packNum;
	nextReadIndex = 0;
	readPack();
	return firstValue;
}
/**
 * @brief 
 * 
 */
void LongDeltaDecoder::readPack() {
	for (int i = 0; i < packNum; i++) {
		readValue(i);
		previous = data[i];
	}
}
/**
 * @brief 
 * 
 * @param buffer 
 */
void LongDeltaDecoder::readHeader(ByteBuffer& buffer) {
	minDeltaBase = buffer.readLong();
	firstValue = buffer.readLong();
}
/**
 * @brief 
 * 
 */
void LongDeltaDecoder::allocateDataArray() {
	if (dataArrayAllocated) {
		delete[] data;
	}
	data = new ll[packNum];
	dataArrayAllocated = 1;
}
/**
 * @brief 
 * 
 * @param result 
 * @param pos 
 * @param width 
 * @return ll 
 */
ll bytesToLong(char* result, int pos, int width) {
	long ret = 0;
	int cnt = pos & 0x07;
	int index = pos >> 3;
	while (width > 0) {
		int m = width + cnt >= 8 ? 8 - cnt : width;
		width -= m;
		ret = ret << m;
		char y = (char)(result[index] & (0xff >> cnt));
		y = (char)((y & 0xff) >> (8 - cnt - m));
		ret = ret | (y & 0xff);
		cnt += m;
		if (cnt == 8) {
			cnt = 0;
			index++;
		}
	}
	return ret;
}
/**
 * @brief 
 * 
 * @param i 
 */
void LongDeltaDecoder::readValue(int i) {
	ll v = bytesToLong(deltaBuf, packWidth * i, packWidth);
	data[i] = previous + minDeltaBase + v;
}
/**
 * @brief 
 * 
 * @param buffer 
 * @return ll 
 */
ll LongDeltaDecoder::readLong(ByteBuffer& buffer) {
	ll r = readT(buffer);
	return r;
}
/**
 * @brief Destroy the Long Delta Decoder:: Long Delta Decoder object
 * 
 */
LongDeltaDecoder::~LongDeltaDecoder() {
	if (dataArrayAllocated)
		delete[] data;
}