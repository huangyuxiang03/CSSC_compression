#pragma once
#include "IntDeltaEncoder.h"
/**
 * @brief Construct a new Int Delta Encoder:: Int Delta Encoder object
 * 
 * @param size 
 */
IntDeltaEncoder::IntDeltaEncoder(int size) : TS_2DIFF_encoder(size) {
	deltaBlockBuffer = new int[blockSize];
	encodingBlockBuffer = new char[blockSize * 4];
	reset();
}
/**
 * @brief Construct a new Int Delta Encoder:: Int Delta Encoder object
 * 
 */
IntDeltaEncoder::IntDeltaEncoder() : IntDeltaEncoder(BLOCK_DEFAULT_SIZE) { }
/**
 * @brief calulate the delta of the given block
 * 
 * @param value 
 */
void IntDeltaEncoder::calcDelta(int value) {
	ll delta = value;// - previousValue;
	if (delta < minDeltaBase)
		minDeltaBase = delta;
	deltaBlockBuffer[writeIndex++] = delta;
}
/**
 * @brief reset the encoder
 * 
 */
void IntDeltaEncoder::reset() {
	firstValue = 0;
	previousValue = 0;
	minDeltaBase = 2147483647;
	for (int i = 0; i < blockSize; i++) {
		encodingBlockBuffer[i] = 0;
		deltaBlockBuffer[i] = 0;
	}
}
/**
 * @brief get the width of the encoding block
 * 
 * @param v 
 * @return int 
 */
int IntDeltaEncoder::getValueWidth(int v) {
	int ans = 0;
	for (int i = 63; i >= 0; i--) {
		if (!(((int)1 << i) & v))
			ans++;
		else
			break;
	}
	return 32 - ans;
}
/**
 * @brief Convert  int value to the the binary string with the starting address pos and the word length width
 * 
 * @param srcNum the int value to be converted
 * @param result the binary string
 * @param pos  the starting address
 * @param width  the word length
 */
void intToBytes(int srcNum, char* result, int pos, int width) {
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
 * @brief convert the int value to a binary string with the length of len
 * 
 * @param num  the int value to be converted
 * @param len  the length of the binary string
 * @return char* 
 */
char* intToBytes(int num, int len) {
	char* byteNum = new char[len];
	for (int ix = 0; ix < len; ix++) {
		byteNum[len - ix - 1] = (char)((num >> ix * 8) & 0xFF);
	}
	return byteNum;
}
/**
 * @brief  convert the ll value to a binary string with the length of len
 * 
 * @param num 
 * @return char* 
 */
char* intToBytes(ll num) {
	return intToBytes(num, 4);
}
/**
 * @brief  write the encoding block to the output stream
 * 
 * @param i 
 */
void IntDeltaEncoder::writeValueToBytes(int i) {
	intToBytes(deltaBlockBuffer[i], encodingBlockBuffer, writeWidth * i, writeWidth);
}
/**
 * @brief  calculate the difference of the given block
 * 
 * @param i 
 */
void IntDeltaEncoder::calcTwoDiff(int i) {
	deltaBlockBuffer[i] = deltaBlockBuffer[i] - minDeltaBase;
}
/**
 * @brief  write the encoding block to the output stream
 * 
 * @param out 
 */
void IntDeltaEncoder::writeHeader(ByteArrayOutputStream& out) {
	char* a = intToBytes(minDeltaBase);
	char* b = intToBytes(firstValue);
	out.write(a, 0, 4);
	out.write(b, 0, 4);
	delete[] a;
	delete[] b;
}
/**
 * @brief  encode the given block to the output stream
 * 
 * @param value 
 * @param out 
 */
void IntDeltaEncoder::encode(int value, ByteArrayOutputStream& out) {
	//cout << value << endl;
	encodeValue(value, out);
}
/**
 * @brief  encode the given block to the output stream
 * 
 * @param value 
 * @param out 
 */
void IntDeltaEncoder::encodeValue(int value, ByteArrayOutputStream& out) {
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
 * @brief calculate the bit width for delta block buffer
 * 
 * @return int 
 */
int IntDeltaEncoder::calculateBitWidthsForDeltaBlockBuffer() {
	int width = 0;
	for (int i = 0; i < writeIndex; i++) {
		width = max(width, getValueWidth(deltaBlockBuffer[i]));
	}
	return width;
}
/**
 * @brief Destroy the Int Delta Encoder:: Int Delta Encoder object
 * 
 */
IntDeltaEncoder::~IntDeltaEncoder() {
	delete[] deltaBlockBuffer;
	delete[] encodingBlockBuffer;
}

