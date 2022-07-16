#pragma once
#ifndef __INTRLEDECODER__
#define __INTRLEDECODER__
#include <iostream>
#include "ByteBuffer.h"
#include "IntPacker.h"
#include "RleDecoder.h"

using namespace std;
class IntRleDecoder : public RleDecoder {
private:
	int currentValue;//!< current value for rle repeated value.
	int* currentBuffer;//!<  buffer to save all values in group using bit-packing.
	IntPacker* packer;//!< packer for unpacking int values.
	bool packerAllocated{ false };
	bool currentBufferAllocated{ false };
public:
	IntRleDecoder() {
		reset();
		currentValue = 0;
	}
	bool readBoolean(ByteBuffer& buffer);
	int readInt(ByteBuffer& buffer);
	void initPacker();
	void readNumberInRle();
	void readBitPackingBuffer(int bitPackedGroupCount, int lastBitPackedNum);
	void reset() {};
	~IntRleDecoder() {
		if (packerAllocated)
			delete packer;
		if (currentBufferAllocated)
			delete[] currentBuffer;
	}
};

#endif // !__INTRLEDECODER__