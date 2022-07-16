#pragma once
#include "IntDeltaDecoder.h"
#include <iostream>
using namespace std;

int IntDeltaDecoder::readT(ByteBuffer& buffer) {
	if (nextReadIndex == readIntTotalCount) {
		return loadIntBatch(buffer);
	}
	return data[nextReadIndex++];
}

int IntDeltaDecoder::loadIntBatch(ByteBuffer& buffer) {
	packNum = buffer.readInt();
	//cout << "packNum" << packNum << endl;
	packWidth = buffer.readInt();
	count++;
	readHeader(buffer);
	time_t start_t, end_t;
	encodingLength = dceil(packNum * packWidth);
	if (deltaBufAllocated)
		delete[] deltaBuf;
	deltaBuf = new char[encodingLength];
	deltaBufAllocated = true;
	//time(&start_t);
	buffer.get(deltaBuf, encodingLength);
	//time(&end_t);
	//cout << "get_time: " << end_t - start_t << endl;
	allocateDataArray();

	previous = firstValue;
	readIntTotalCount = packNum;
	nextReadIndex = 0;
	//time(&start_t);
	readPack();
	//time(&end_t);
	//cout << "cal_time: " << end_t - start_t << endl;
	return firstValue;
}

void IntDeltaDecoder::readPack() {
	for (int i = 0; i < packNum; i++) {
		readValue(i);
		previous = data[i];
	}
}

void IntDeltaDecoder::readHeader(ByteBuffer& buffer) {
	minDeltaBase = buffer.readInt();
	firstValue = buffer.readInt();
}

void IntDeltaDecoder::allocateDataArray() {
	if (dataArrayAllocated) {
		delete[] data;
	}
	data = new int[packNum];
	dataArrayAllocated = 1;
}

int bytesToint(char* result, int pos, int width) {
	int ret = 0;
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

void IntDeltaDecoder::readValue(int i) {
	int v = bytesToint(deltaBuf, packWidth * i, packWidth);
	data[i] = v + minDeltaBase; //previous + minDeltaBase + v;
}

int IntDeltaDecoder::readInt(ByteBuffer& buffer) {
	int r = readT(buffer);
	return r;
}

IntDeltaDecoder::~IntDeltaDecoder() {
	if (dataArrayAllocated)
		delete[] data;
}