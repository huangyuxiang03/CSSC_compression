#pragma once
#include "LongDeltaEncoder.h"
/**
 * @brief Construct a new Long Delta Encoder:: Long Delta Encoder object
 * 
 * @param size 
 */
LongDeltaEncoder::LongDeltaEncoder(int size) : TS_2DIFF_encoder(size) {
	deltaBlockBuffer = new ll[blockSize];
	encodingBlockBuffer = new char[blockSize * 8];
	reset();
}
/**
 * @brief Construct a new Long Delta Encoder:: Long Delta Encoder object
 * 
 */
LongDeltaEncoder::LongDeltaEncoder() : LongDeltaEncoder(BLOCK_DEFAULT_SIZE) { }
/**
 * @brief 
 * 
 * @param value 
 */
void LongDeltaEncoder::calcDelta(ll value) {
	ll delta = value - previousValue;
	if (delta < minDeltaBase)
		minDeltaBase = delta;
	deltaBlockBuffer[writeIndex++] = delta;
}
/**
 * @brief 
 * 
 */
void LongDeltaEncoder::reset() {
	firstValue = 0;
	previousValue = 0;
	minDeltaBase = 9223372036854775807;
	for (int i = 0; i < blockSize; i++) {
		encodingBlockBuffer[i] = 0;
		deltaBlockBuffer[i] = 0;
	}
}
/**
 * @brief 
 * 
 * @param v 
 * @return int 
 */
int LongDeltaEncoder::getValueWidth(ll v) {
	int ans = 0;
	for (int i = 63; i >= 0; i--) {
		if (!(((ll)1 << i) & v))
			ans++;
		else
			break;
	}
	return 64-ans;
}
/**
 * @brief 
 * 
 * @param srcNum 
 * @param result 
 * @param pos 
 * @param width 
 */
void longToBytes(ll srcNum, char* result, int pos, int width) {
	int cnt = pos & (0x07);
	int index = pos >> 3;
	while (width > 0) {
		int m = width + cnt >= 8 ? 8 - cnt : width;
		width -= m;
		int mask = 1 << (8 - cnt);
		cnt += m;
		char y = (char)(srcNum >> width);
		y = (char)(y << (8 - cnt));
		mask = ~(mask - (1 << (8 - cnt)));
		result[index] = (char)(result[index] & mask | y);
		srcNum = srcNum & ~(-1 << width);
		if (cnt == 8) {
			index++;
			cnt = 0;
		}
	}
}
/**
 * @brief 
 * 
 * @param num 
 * @param len 
 * @return char* 
 */
char* longToBytes(ll num, int len) {
	char* byteNum = new char[len];
	for (int ix = 0; ix < len; ix++) {
		byteNum[len - ix - 1] = (char)((num >> ix * 8) & 0xFF);
	}
	return byteNum;
}
/**
 * @brief 
 * 
 * @param num 
 * @return char* 
 */
char* longToBytes(ll num) {
	return longToBytes(num, 8);
}
/**
 * @brief 
 * 
 * @param i 
 */
void LongDeltaEncoder::writeValueToBytes(int i) {
	longToBytes(deltaBlockBuffer[i], encodingBlockBuffer, writeWidth * i, writeWidth);
}
/**
 * @brief 
 * 
 * @param i 
 */
void LongDeltaEncoder::calcTwoDiff(int i) {
	deltaBlockBuffer[i] = deltaBlockBuffer[i] - minDeltaBase;
}
/**
 * @brief 
 * 
 * @param out 
 */
void LongDeltaEncoder::writeHeader(ByteArrayOutputStream& out) {
	char* a = longToBytes(minDeltaBase);
	char* b = longToBytes(firstValue);
	out.write(a, 0, 8);
	out.write(b, 0, 8);
	delete[] a;
	delete[] b;
}
/**
 * @brief 
 * 
 * @param value 
 * @param out 
 */
void LongDeltaEncoder::encode(ll value, ByteArrayOutputStream &out) {
	encodeValue(value, out);
}
/**
 * @brief 
 * 
 * @param value 
 * @param out 
 */
void LongDeltaEncoder::encodeValue(ll value, ByteArrayOutputStream &out) {
	if (writeIndex == -1) {
		writeIndex++;
		firstValue = value;
		previousValue = firstValue;
		return;
	}
	calcDelta(value);
	previousValue = value;
	if (writeIndex == blockSize) {
		flush(out);
	}
}
/**
 * @brief 
 * 
 * @return int 
 */
int LongDeltaEncoder::calculateBitWidthsForDeltaBlockBuffer() {
	int width = 0;
	for (int i = 0; i < writeIndex; i++) {
		width = max(width, getValueWidth(deltaBlockBuffer[i]));
	}
	return width;
}
/**
 * @brief Destroy the Long Delta Encoder:: Long Delta Encoder object
 * 
 */
LongDeltaEncoder::~LongDeltaEncoder() {
	delete[] deltaBlockBuffer;
	delete[] encodingBlockBuffer;
}

