#include "ByteBufferV2.h"
// constructor: copy fp to filepath, then do nothing.	[lr]
ByteBufferV2::ByteBufferV2(std::string fp) {
	filepath = fp;
}

// load the data from _bytes to bytes. use memcpy to enhance speed. [lr]
ByteBufferV2::ByteBufferV2(std::vector<std::uint8_t> _bytes) {
	bytes = new uint8_t[sizeof(_bytes)];
	if (!_bytes.empty()) {
		memcpy(bytes, &_bytes[0], _bytes.size() * sizeof(uint8_t));
		bytesAllocated = true;
	}
}

// calculate how many bytes left. (use currentPosition and bytesLength to calculate this value)	[lr]
int ByteBufferV2::remaining() {
	return bytesLength - (currentPosition - bytes);
}

// if there is bytes left, return true, otherwise return false.	[lr]
bool ByteBufferV2::hasRemaining() {
	return bytesLength > (currentPosition - bytes + 1);
}

// read 4 bytes and concatenate to an int then return. currentPosition movebackwards 4 bytes. [lr]
int ByteBufferV2::readInt() {
	int tempInt = *reinterpret_cast<int*>(currentPosition);
	currentPosition += 4;
	return tempInt;
}

// read a byte and change into char.	[lr]
char ByteBufferV2::readByte() {
	char tempChar = *reinterpret_cast<char*>(currentPosition);
	currentPosition += 1;
	return tempChar;
}

// read a byte and change into uint8_t	[lr]
std::uint8_t ByteBufferV2::readuchar() {
	std::uint8_t tempUint8_t = *reinterpret_cast<uint8_t*>(currentPosition);
	currentPosition += 1;
	return tempUint8_t;
}