#pragma once
#include <vector>
#include <string>
using namespace std;
#ifndef __ByteBuffer__
#define __ByteBuffer__

class ByteBuffer {
private:
	std::vector<std::uint8_t> bytes;
	string filepath;
public:
	ByteBuffer() {};
	ByteBuffer(string fp) {
		this->filepath = fp;
	};
	ByteBuffer(std::vector<std::uint8_t> bytes) {
		vector <std::uint8_t>().swap(this->bytes);
		this->bytes.insert(this->bytes.begin(), bytes.begin(),bytes.end());
	};
	int remaining();
	int readInt();
	char readByte();
	long long readLong();
	float readFloat();
	void get(char* dst, int len);//copy the current len'th byte to dst
};

#endif
