#include "ByteBuffer.h"

int ByteBuffer::remaining()
{
	return bytes.size();
}

int ByteBuffer::readInt()
{
	return 0;
}

char ByteBuffer::readByte()
{
	return 0;
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
