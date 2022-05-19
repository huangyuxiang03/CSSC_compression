#pragma once

#ifndef __FUNCTIONENCODER__
#define __FUNCTIONENCODER__
#include "../../CSSC_compression_code/CSSC_compression_code/ByteArrayOutputStream.h"

class FunctionEncoder {
protected:
	char* encodingBlockBuffer;
	int blockSize;
	int definitionalDomainSize;
public:
	FunctionEncoder() {
		blockSize = 16;
		definitionalDomainSize = 256;
	}
	FunctionEncoder(int bs,int dds) {
		blockSize = bs;
		definitionalDomainSize = dds;
	}
	int getBlockSize();
	int getDefinitionalDomainSize();
	// how blockSize can not is not divisible by definitionalDomainSize

};


#endif // !__FUNCTIONENCODER__