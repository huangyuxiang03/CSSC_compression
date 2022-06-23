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

bool ByteBuffer::hasRemaining()
{
	if (bytes.size() > 0) return true;
	return false;
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

void ByteBuffer::get(std::vector<uint8_t>& tmp, int offset, int length)
{
	if (length > remaining()) {
		cout << "under flow exception" << endl;
		return;
	}
	/*int maxi = offset + length;
	for (int i = offset; i < maxi; i++) tmp[i] = readuchar();*/
	memcpy(tmp.data(), bytes.data(), length);
	bytes.erase(bytes.begin(), bytes.begin() + length);
}

void ByteBuffer::divideTo3Parts(ByteBuffer& b2, ByteBuffer& b3) {
	int length_b3;
	memcpy(&length_b3, bytes.data() + bytes.size() - 4, 4);
	bytes.erase(bytes.end() - 4, bytes.end());
	b3.bytes.insert(b3.bytes.begin(), bytes.end() - length_b3, bytes.end());
	bytes.erase(bytes.end() - length_b3, bytes.end());

	int length_b2;
	memcpy(&length_b2, bytes.data() + bytes.size() - 4, 4);
	bytes.erase(bytes.end() - 4, bytes.end());
	b2.bytes.insert(b2.bytes.begin(), bytes.end() - length_b2, bytes.end());
	bytes.erase(bytes.end() - length_b2 - 4, bytes.end());
}