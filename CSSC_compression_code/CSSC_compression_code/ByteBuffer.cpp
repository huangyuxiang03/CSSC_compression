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
	char buffer_int;
	this->bytes >> buffer_int;
	return buffer_int;
}

long long ByteBuffer::readLong()
{
	return 0;
}

float ByteBuffer::readFloat()
{
	return 0.0f;
}

void ByteBuffer::get(char* dst, int len)
{
}
