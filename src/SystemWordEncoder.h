#pragma once
#include "IntRleEncoder.h"
#include "IntDeltaEncoder.h"
#include "ByteArrayOutputStreamV2.h"

#ifndef __SYSTEMWORD__
#define __SYSTEMWORD__

class SystemWordEncoder {
private:
	IntDeltaEncoder encoder[288];
	int count{ 0 };
public:
	void encode(int num, ByteArrayOutputStream* out);
	void flush(ByteArrayOutputStream* out);
};

#endif // !__SYS__
