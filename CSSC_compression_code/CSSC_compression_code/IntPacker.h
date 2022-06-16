#pragma once
#ifndef __INTPACKER__
#define __INTPACKER__
#include <iostream>
#include <vector>
using namespace std;

class IntPacker {
private:
	int NUM_OF_INTS;
	int width;
public:
	IntPacker() {
		NUM_OF_INTS = 8;
	}
	IntPacker(int width) {
		this->width = width;
	}
	~IntPacker() {};
	void pack8Values(int* values, int offset, vector<std::uint8_t>& buf);
	void unpack8Values(vector<std::uint8_t>& buf, int offset, int* values);
	void unpackAllValues(vector<std::uint8_t>& buf, int length, int* values);
	void setWidth(int width);
};

#endif // !__INTPACKER__