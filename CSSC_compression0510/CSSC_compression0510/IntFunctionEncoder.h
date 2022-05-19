#pragma once


#ifndef __INTFUNCTIONENCODER__
#define __INTFUNCTIONENCODER__
#include <cmath>
#include "FunctionEncoder.h"
#include "Array.h"
#include "../../CSSC_compression_code/CSSC_compression_code/ByteArrayOutputStream.h"


class IntFunctionEncoder : public FunctionEncoder {
protected:
	int eta;
	int sigma;
	int beta; // linear slope
	int c;
	Array<int> readyEncodeBuffer;
	Array<int> bufferKey;
	int* dictinctPool;
	int* keyPool;
	int curDictinctPoolNum;
	//int curBufferNum;
public:
	IntFunctionEncoder(){
		eta=0;
		sigma=0;
		beta=0; // linear slope
		c=0;
		curDictinctPoolNum = 0;
		//curBufferNum = 0;
		//readyEncodeBuffer = new int[definitionalDomainSize];
		dictinctPool = new int[definitionalDomainSize];
		keyPool = new int[definitionalDomainSize];
	}
	void addDictionary(int num);
	void encode(int num, ByteArrayOutputStream baos);
};

#endif // !__INTFUNCTIONENCODER__