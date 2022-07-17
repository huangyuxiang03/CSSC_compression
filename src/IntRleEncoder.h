#pragma once
#ifndef __INTRLEENCODER__
#define __INTRLEENCODER__
#include <iostream>
#include "ByteArrayOutputStreamV2.h"
#include "RleEncoder.h"
#include "IntPacker.h"
#include "array.h"

using namespace std;

class IntRleEncoder : public RleEncoder {
protected:
	array<int> values;
	int preValue;
	int* bufferedValues;
	IntPacker packer;
public:
	IntRleEncoder() {
		bufferedValues = new int[RLE_MIN_REPEATED_NUM];
		preValue = 0;
		//values = new ArrayList<>();
	}
	~IntRleEncoder() {
		values.empty();
		delete[] bufferedValues;
	}
	void encode(int value, ByteArrayOutputStream& out);
	int getIntMaxBitWidth(array<int> list);
	void encode(bool value, ByteArrayOutputStream& out);
	void flush(ByteArrayOutputStream& out);
	void reset(); 
	void writeRleRun();
	void clearBuffer();
	void convertBuffer();
	void encodeValue(int value);
};


#endif // !__INTRLEENCODER__