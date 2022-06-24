#include "ByteBufferV2.h"

long long ByteBufferV2::readLong() {
	long long rtn;
	memcpy(&rtn, currentPosition, 8);
	currentPosition += 8;
	return rtn;
}

float ByteBufferV2::readFloat() {
	float rtn;
	memcpy(&rtn, currentPosition, 4);
	currentPosition += 4;
	return rtn;
}

void ByteBufferV2::get(char* dst, int len) {
	for (int i = 0; i < len; i++) {
		dst[i] = currentPosition[len - i - 1];
	}
	currentPosition += len;
	return;
}

void ByteBufferV2::get(std::vector<uint8_t>& tmp, int offset, int length) {
	memcpy(tmp.data(), currentPosition, length);
	currentPosition += length;
}

std::vector<std::uint8_t> ByteBufferV2::Bytes() {
	std::vector<std::uint8_t> rtn(bytesLength);
	memcpy(rtn.data(), bytes, bytesLength);
	return rtn;
}

void ByteBufferV2::divideTo3Parts(ByteBufferV2& b2, ByteBufferV2& b3) {
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

ByteBufferV2::~ByteBufferV2() {
	if (bytesAllocated)
		delete[] bytes;
}

