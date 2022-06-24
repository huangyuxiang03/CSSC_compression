#pragma once
#include <vector>
#include <string>
#include <cstring>
using namespace std;
#ifndef __ByteBufferOld__
#define __ByteBufferOld__

class ByteBufferOld {
private:
	std::vector<std::uint8_t> bytes;
	std::string filepath;
public:
	ByteBufferOld() {};
	ByteBufferOld(std::string fp) {
		this->filepath = fp;
	};
	ByteBufferOld(std::vector<std::uint8_t> bytes) {
		vector <std::uint8_t>().swap(this->bytes);
		this->bytes = bytes;
		//this->bytes.insert(this->bytes.begin(), bytes.begin(),bytes.end());
	};
	int remaining();
	bool hasRemaining();
	int readInt();
	char readByte();
	std::uint8_t readuchar();
	long long readLong();
	float readFloat();
	void get(char* dst, int len);//copy the current len'th byte to dst
	void get(std::vector<uint8_t>& tmp, int offset, int length);
	std::vector<std::uint8_t> Bytes() {
		return bytes;
	}
	void divideTo3Parts(ByteBufferOld& b2, ByteBufferOld& b3);
};

#endif
