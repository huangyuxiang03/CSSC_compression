#pragma once
#ifndef __ByteBuffer__
#define __ByteBuffer__

class ByteBuffer {
private:

public:
	int remaining();
	int readInt();
	char readByte();
	long long readLong();
	float readFloat();
};

#endif
