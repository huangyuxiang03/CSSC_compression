#pragma once
#include <vector>
#include <string>
#include <cstring>
#ifndef __ByteBuffer__
#define __ByteBuffer__
/**
* @note
	First we new a large block of uint8_t[], then we read data from file and store in the memory we newed.
	The pointer bytes is always pointing to the header of the whole data block, i.e., the position of bytes never changes after reading in data.
	currentPosition is moving while reading data, i.e., it first pointing to the header, then it moves backwards.
	The total length (number of bytes) should be ascertained while reading data.
*/
class ByteBuffer {
private:
	std::uint8_t* bytes; //!< the pointer of all data in memory
	std::string filepath; //!< the filepath to read data
	int bytesLength{0}; //!< the number of bytes of data
	std::uint8_t* currentPosition; //!< the current position of data
	bool bytesAllocated{ false }; //!< turn bytesAllocated to true after allocating memory for bytes!!
public:
	ByteBuffer() { };
	ByteBuffer(std::string fp);
	ByteBuffer(std::vector<std::uint8_t> _bytes);
	int remaining();
	bool hasRemaining();
	int readInt();
	char readByte();
	std::uint8_t readuchar();
	long long readLong();
	float readFloat();
	void get(char* dst, int len);
	void get(std::vector<uint8_t>& tmp, int offset, int length);
	std::vector<std::uint8_t> Bytes();
	void divideTo3Parts(ByteBuffer& b2, ByteBuffer& b3);
	ByteBuffer& operator=(ByteBuffer& b);
	~ByteBuffer();
};

#endif