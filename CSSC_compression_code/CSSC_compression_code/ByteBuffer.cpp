#include "ByteBuffer.h"
#include <time.h>
#include <iostream>
using namespace std;

template <typename T>
std::vector<std::uint8_t>& operator<<(std::vector<std::uint8_t>& in, T& out)
{
	if (in.size() >= sizeof(T)) {
		/*//out = *reinterpret_cast<T*>(in.data());
		//memcpy(&out, in.data(), sizeof(T));

		//in.erase(in.begin(), in.begin() + sizeof(T));
		unsigned char* p = new unsigned char[sizeof(T)];
		for (int i = 0; i < sizeof(T); i++) {
			p[sizeof(T) - 1 - i] = *(in.data() + i);
		}
		//if(sizeof(out) == 8)
			//out = *reinterpret_cast<T*>(p);
		//else*/
		out = *reinterpret_cast<T*>(in.data());
		in.erase(in.begin(), in.begin() + sizeof(T));
		char* pp = (char*)&out;
		//delete[] p;
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
	this->bytes  << buffer_int;
	return buffer_int;
}

char ByteBuffer::readByte()
{
	char buffer_byte;
	this->bytes << buffer_byte;
	return buffer_byte;
}

std::uint8_t ByteBuffer::readuchar()
{
	std::uint8_t uc;
	this->bytes << uc;
	return uc;
}

long long ByteBuffer::readLong()
{
	long long buffer_ll=0;
	this->bytes << buffer_ll;
	return buffer_ll;
}

float ByteBuffer::readFloat()
{
	float buffer_float = 0.0;
	this->bytes << buffer_float;
	return buffer_float;
}

void ByteBuffer::get(char* dst, int len)
{
	int max = len;
	//if (len > bytes.size()) max = bytes.size();
	char* buffer_byte = new char[max];
	memcpy(buffer_byte, bytes.data(), max);
	//if (len ) {
	//	bytes.erase(bytes.begin(), bytes.end());
	//}
	//else 
	bytes.erase(bytes.begin(), bytes.begin() + max);
	for (int i = 0; i < max; i++) {
		dst[max - i - 1] = buffer_byte[i];
	}
	delete[] buffer_byte;

	//for (int i = 0; i < len; i++) {
	//	char buffer_byte;
	//	this->bytes << dst[len- i -1];
	//}
}
