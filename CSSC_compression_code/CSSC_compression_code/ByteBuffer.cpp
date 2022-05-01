#include "ByteBuffer.h"

template <typename T>
std::vector<std::uint8_t>& operator>>(std::vector<std::uint8_t>& in, T& out)
{
	if (in.size() >= sizeof(T)) {
		out = *reinterpret_cast<T*>(in.data());
		in.erase(in.begin(), in.begin() + sizeof(T));
	}
	else {
		out = T{ 0 };
	}
	return in;
}
int ByteBuffer::remaining()
{
	return bytes.size();
}

int ByteBuffer::readInt()
{
	int buffer_int = 0;
	this->bytes  >> buffer_int;
	return buffer_int;
}

char ByteBuffer::readByte()
{
	char buffer_byte;
	this->bytes >> buffer_byte;
	return buffer_byte;
}

long long ByteBuffer::readLong()
{
	long long buffer_ll=0;
	this->bytes >> buffer_ll;
	return buffer_ll;
}

float ByteBuffer::readFloat()
{
	float buffer_float = 0.0;
	this->bytes >> buffer_float;
	return buffer_float;
}

void ByteBuffer::get(char* dst, int len)
{
	for (int i = 0; i < len; i++) {
		char buffer_byte;
		this->bytes >> dst[i];
	}
}
