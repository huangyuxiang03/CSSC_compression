#include "ByteBuffer.h"
#include <iostream>
/**
 * @brief read 8 bits and concatenate into a long long.
 * @return long long
 * @author hyx
 */
long long ByteBuffer::readLong() {
	long long rtn;
	memcpy(&rtn, currentPosition, 8);
	currentPosition += 8;
	return rtn;
}
/**
 * @brief read 4 bits and concatenate into a float.
 * @return float
 * @author hyx
 */
float ByteBuffer::readFloat() {
	float rtn;
	memcpy(&rtn, currentPosition, 4);
	currentPosition += 4;
	return rtn;
}
/**
 * @brief copy the current len'th byte to dst (in reverse order).
 * @param dst
 * @param len
 * @return void
 * @author hyx
 */
void ByteBuffer::get(char* dst, int len) {
	for (int i = 0; i < len; i++) {
		dst[i] = currentPosition[len - i - 1];
	}
	currentPosition += len;
	return;
}
/**
 * @brief copy the current len'th bits to tmp in normal order (offset is useless).
 * @param tmp
 * @param offset
 * @param length
 * @return void
 * @author hyx
 */
void ByteBuffer::get(std::vector<uint8_t>& tmp, int offset, int length) {
	memcpy(tmp.data(), currentPosition, length);
	currentPosition += length;
}

void ByteBuffer::get(array<uint8_t>& tmp, int offset, int length) {
	memcpy(tmp.data(), currentPosition, length);
	currentPosition += length;
}
/**
 * @brief turn all bytes into a vector.
 * @param None
 * @return std::vector<std::uint8_t>
 * @author hyx
 */
std::vector<std::uint8_t> ByteBuffer::Bytes() {
	std::vector<std::uint8_t> rtn(bytesLength);
	memcpy(rtn.data(), bytes, bytesLength);
	return rtn;
}
/**
 * @brief cut the buffer into three parts, which are head, middle and tail.
 * @param b2
 * @param b3
 * @return void
 * @author hyx
 */
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
	tail -= length_b2;
	tail -= 4;
	bytesLength = tail - bytes;
	currentPosition = bytes;
}
/**
 * @brief Destroy the Byte Buffer:: Byte Buffer object
 * @param None
 * @author lrs
 */
ByteBuffer::~ByteBuffer() {
	if (bytesAllocated)
		delete[] bytes;
}
/**
 * @brief constructor: copy fp to filepath, then read from binary file.
 * @param fp
 * @author lr
 */
ByteBuffer::ByteBuffer(std::string fileName) {
	filepath = fileName;
	// open file as binary file
	FILE* fp = fopen(fileName.c_str(), "rb+");

	// calculate the length of bytes
	fseek(fp, 0, SEEK_END);
	bytesLength = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	bytes = new uint8_t[bytesLength];
	bytesAllocated = true;
	currentPosition = bytes;
	fread(bytes, bytesLength, 1, fp);
	fclose(fp);
}
/**
 * @brief load the data from _bytes to bytes. use memcpy to enhance speed.
 * @param _bytes
 * @author lr
 */
ByteBuffer::ByteBuffer(std::vector<std::uint8_t> _bytes) {
	bytes = new uint8_t[_bytes.size()];
	if (!_bytes.empty()) {
		memcpy(bytes, &_bytes[0], _bytes.size() * sizeof(uint8_t));
		bytesAllocated = true;
		bytesLength = _bytes.size();
		currentPosition = bytes;
	}
}
/**
 * @brief calculate how many bytes left. (use currentPosition and bytesLength to calculate this value)
 * @param None
 * @return int
 * @author lr
 */
int ByteBuffer::remaining() {
	return bytesLength - (currentPosition - bytes);
}
/**
 * @brief if there is bytes left, return true, otherwise return false.
 * @param None
 * @return true
 * @return false
 * @author lr
 */
bool ByteBuffer::hasRemaining() {
	return bytesLength >= (currentPosition - bytes + 1);
}
/**
 * @brief read 4 bytes and concatenate to an int then return. currentPosition movebackwards 4 bytes.
 * @param None
 * @return int
 * @author lr
 */
int ByteBuffer::readInt() {
	int tempInt = *reinterpret_cast<int*>(currentPosition);
	currentPosition += 4;
	return tempInt;
}
/**
 * @brief read a byte and change into char, and currentPosition movebackwards 1 byte.
 * @param None
 * @return char
 * @author lr
 */
char ByteBuffer::readByte() {
	char tempChar = *reinterpret_cast<char*>(currentPosition);
	currentPosition += 1;
	return tempChar;
}
/**
 * @brief read a byte and change into uint8_t.
 * @param None
 * @return std::uint8_t
 * @author lr
 */
std::uint8_t ByteBuffer::readuchar() {
	std::uint8_t tempUint8_t = *reinterpret_cast<uint8_t*>(currentPosition);
	currentPosition += 1;
	return tempUint8_t;
}
/**
 * @brief read a byte and change into uint8_t.
 * @param None
 * @return std::uint8_t
 * @author hyx
 */
ByteBuffer& ByteBuffer::operator=(ByteBuffer& b) {
	if (this->bytesAllocated)
		delete[] bytes;
	bytes = new uint8_t[b.bytesLength];
	memcpy(bytes, b.bytes, b.bytesLength);
	bytesLength = b.bytesLength;
	filepath = b.filepath;
	currentPosition = bytes + (b.currentPosition - b.bytes);
	return *this;
}