#pragma once
#include <vector>
#include <string>
#include <cstring>
#ifndef __ByteBuffer__
#define __ByteBuffer__

class ByteBuffer {
private:
	std::uint8_t* bytes; // the pointer of all data in memory
	std::string filepath; // the filepath to read data
	int bytesLength{0}; // the number of bytes of data
	std::uint8_t* currentPosition; // the current position of data
	/*
	* Note: First we new a large block of uint8_t[], then we read data from file and store in the memory we newed.
	*	The pointer bytes is always pointing to the header of the whole data block, i.e., the position of bytes never changes after reading in data.
	*	currentPosition is moving while reading data, i.e., it first pointing to the header, then it moves backwards.
	*	The total length (number of bytes) should be ascertained while reading data.
	*/

	bool bytesAllocated{ false }; // turn bytesAllocated to true after allocating memory for bytes!!
public:
	ByteBuffer() { }; // empty constructor;
	ByteBuffer(std::string fp); // constructor: copy fp to filepath, then do nothing.	[lr]
	ByteBuffer(std::vector<std::uint8_t> _bytes); // load the data from _bytes to bytes. use memcpy to enhance speed. [lr]
	int remaining(); // calculate how many bytes left. (use currentPosition and bytesLength to calculate this value)	[lr]
	bool hasRemaining(); // if there is bytes left, return true, otherwise return false.	[lr]
	int readInt(); // read 4 bytes and concatenate to an int then return. currentPosition movebackwards 4 bytes. [lr]
	char readByte(); // read a byte and change into char.	[lr]
	std::uint8_t readuchar(); // read a byte and change into uint8_t	[lr]
	long long readLong(); //read 8 bytes and concatenate into a long long	[hyx]
	float readFloat(); // read 4 bytes and concatenate into a float	[hyx]
	void get(char* dst, int len);//copy the current len'th byte to dst (in reverse order)	[hyx]
	void get(std::vector<uint8_t>& tmp, int offset, int length); // copy the current len'th bytes to tmp in normal order (offset is useless)	[hyx]
	std::vector<std::uint8_t> Bytes(); // turn all bytes into a vector	[hyx]
	void divideTo3Parts(ByteBuffer& b2, ByteBuffer& b3); //	[hyx]
	ByteBuffer& operator=(ByteBuffer& b);
	~ByteBuffer();
};

#endif