#pragma once
#ifndef __INTPACKER__
#define __INTPACKER__
#include <iostream>
#include "array.h"
using namespace std;

class IntPacker {
private:
	int NUM_OF_INTS=8;
	int width;
public:
	IntPacker() {
		this->width = 0;
	}
	IntPacker(int width) {
		this->width = width;
	}
	~IntPacker() {};
	void pack8Values(int* values, int offset, array<std::uint8_t>& buf);
	void unpack8Values(array<std::uint8_t>& buf, int offset, int* values);
	void unpackAllValues(array<std::uint8_t>& buf, int length, int* values);
	void setWidth(int width);
};

#endif // !__INTPACKER__