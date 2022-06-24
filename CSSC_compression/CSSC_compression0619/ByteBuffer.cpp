#include "ByteBuffer.h"

long long ByteBuffer::readLong() {
	long long rtn;
	memcpy(&rtn, currentPosition, 8);
	currentPosition += 8;
	return rtn;
}

float ByteBuffer::readFloat() {
	float rtn;
	memcpy(&rtn, currentPosition, 4);
	currentPosition += 4;
	return rtn;
}

void ByteBuffer::get(char* dst, int len) {
	for (int i = 0; i < len; i++) {
		dst[i] = currentPosition[len - i - 1];
	}
	currentPosition += len;
	return;
}

void ByteBuffer::get(std::vector<uint8_t>& tmp, int offset, int length) {
	memcpy(tmp.data(), currentPosition, length);
	currentPosition += length;
}

std::vector<std::uint8_t> ByteBuffer::Bytes() {
	std::vector<std::uint8_t> rtn(bytesLength);
	memcpy(rtn.data(), bytes, bytesLength);
	return rtn;
}

void ByteBuffer::divideTo3Parts(ByteBuffer& b2, ByteBuffer& b3) {
	uint8_t* tail = bytes + bytesLength;

	int length_b3;
	memcpy(&length_b3, tail - 4, 4);
	tail -= 4;
	b3.bytes = new uint8_t[length_b3];
	b3.bytesLength = length_b3;
	b3.currentPosition = b3.bytes;
	b3.bytesAllocated = true;
	memcpy(b3.bytes, tail - length_b3, length_b3);
	tail -= length_b3;

	int length_b2;
	memcpy(&length_b2, tail - 4, 4);
	tail -= 4;
	b2.bytes = new uint8_t[length_b2];
	b2.bytesLength = length_b2;
	b2.currentPosition = b2.bytes;
	b2.bytesAllocated = true;
	memcpy(b2.bytes, tail - length_b2, length_b2);
	tail -= 4;
}

ByteBuffer::~ByteBuffer() {
	if (bytesAllocated)
		delete[] bytes;
}

ByteBuffer::ByteBuffer(std::string fp) {
	filepath = fp;
}

// load the data from _bytes to bytes. use memcpy to enhance speed. [lr]
ByteBuffer::ByteBuffer(std::vector<std::uint8_t> _bytes) {
	bytes = new uint8_t[sizeof(_bytes)];
	if (!_bytes.empty()) {
		memcpy(bytes, &_bytes[0], _bytes.size() * sizeof(uint8_t));
		bytesAllocated = true;
	}
}

// calculate how many bytes left. (use currentPosition and bytesLength to calculate this value)	[lr]
int ByteBuffer::remaining() {
	return bytesLength - (currentPosition - bytes);
}

// if there is bytes left, return true, otherwise return false.	[lr]
bool ByteBuffer::hasRemaining() {
	return bytesLength > (currentPosition - bytes + 1);
}

// read 4 bytes and concatenate to an int then return. currentPosition movebackwards 4 bytes. [lr]
int ByteBuffer::readInt() {
	int tempInt = *reinterpret_cast<int*>(currentPosition);
	currentPosition += 4;
	return tempInt;
}

// read a byte and change into char.	[lr]
char ByteBuffer::readByte() {
	char tempChar = *reinterpret_cast<char*>(currentPosition);
	currentPosition += 1;
	return tempChar;
}

// read a byte and change into uint8_t	[lr]
std::uint8_t ByteBuffer::readuchar() {
	std::uint8_t tempUint8_t = *reinterpret_cast<uint8_t*>(currentPosition);
	currentPosition += 1;
	return tempUint8_t;
}