#pragma once

#ifndef __RLEENCODER__
#define __RLEENCODER__
#include <iostream>
#include "array.h"
#include "ByteArrayOutputStreamV2.h"

using namespace std;
//template <typename T>
class RleEncoder {
protected:
	//array<T> values;
	int bitWidth{0};
	int repeatCount{0};
	int bitPackedGroupCount{0};
	int numBufferedValues{0};
	array<array<std::uint8_t>> bytesBuffer;
	bool isBitPackRun{0};
	//T preValue;
	//T[] bufferedValues;
	bool isBitWidthSaved{0};
	ByteArrayOutputStream byteCache;
	int RLE_MIN_REPEATED_NUM;
	int RLE_MAX_BIT_PACKED_NUM;
	int RLE_MAX_REPEATED_NUM;

public:
	RleEncoder() {
		isBitPackRun = false;
		isBitWidthSaved = false;
		//byteCache = new ByteArrayOutputStream();
		RLE_MIN_REPEATED_NUM = 8;
		RLE_MAX_BIT_PACKED_NUM = 63;
		RLE_MAX_REPEATED_NUM = 0x7FFF;
	}
	~RleEncoder() {
		this->bytesBuffer.empty();
		byteCache.reset();
	}
	void reset();
	void flushrle(ByteArrayOutputStream& out);
	virtual void writeRleRun() {};
	virtual void clearBuffer() {};
	virtual void convertBuffer(){};
	void writeOrAppendBitPackedRun();
	int writeUnsignedVarInt(int value, ByteArrayOutputStream& out);
	//static int getIntMaxBitWidth(array<int> list);
	static int numberOfLeadingZeros(int i);
	static void writeIntLittleEndianPaddedOnBitWidth(int value, ByteArrayOutputStream& out, int bitWidth);
	void endPreviousBitPackedRun(int lastBitPackedNum);

};

#endif // !__RLEENCODER__

//template<typename T>
//inline void RleEncoder<T>::reset()
//{
//	numBufferedValues = 0;
//	repeatCount = 0;
//	bitPackedGroupCount = 0;
//	bytesBuffer.clear();
//	isBitPackRun = false;
//	isBitWidthSaved = false;
//	byteCache = = new ByteArrayOutputStream();
//	values.clear();
//}
//
//template<typename T>
//inline void RleEncoder<T>::flush(ByteArrayOutputStream out)
//{
//	int lastBitPackedNum = numBufferedValues;
//	if (repeatCount >= this->RLE_MIN_REPEATED_NUM) {
//		writeRleRun();
//	}
//	else if (numBufferedValues > 0) {
//		clearBuffer();
//		writeOrAppendBitPackedRun();
//		endPreviousBitPackedRun(lastBitPackedNum);
//	}
//	else {
//		endPreviousBitPackedRun(this->RLE_MIN_REPEATED_NUM);
//	}
//	// write length
//	ReadWriteForEncodingUtils.writeUnsignedVarInt(byteCache.size(), out);
//	out(byteCache.getBytes());
//	reset();
//}
//
//template<typename T>
//inline void RleEncoder<T>::writeOrAppendBitPackedRun()
//{
//}

