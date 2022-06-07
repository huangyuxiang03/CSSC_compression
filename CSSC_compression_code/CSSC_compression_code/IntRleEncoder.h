#pragma once
#ifndef __INTRLEENCODER__
#define __INTRLEENCODER__
#include <iostream>
#include "ByteArrayOutputStream.h"
#include "RleEncoder.h"
#include "IntPacker.h"

using namespace std;

class IntRleEncoder : RleEncoder {
protected:
	vector<int> values;
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
		vector <int>().swap(values);
		delete[] bufferedValues;
	}
	void encode(int value, ByteArrayOutputStream& out);
	int getIntMaxBitWidth(vector<int> list);
	void encode(bool value, ByteArrayOutputStream& out);
	void flush(ByteArrayOutputStream& out);
	void reset(); 
	void writeRleRun();
	void clearBuffer();
	void convertBuffer();
	void encodeValue(int value);
};


#endif // !__INTRLEENCODER__