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
	int alpha;
	Array<int>* readyEncodeBuffer;
	Array<int>* bufferKey;
	int* dictinctPool;
	int* keyPool;
	int curDictinctPoolNum;
	//int curBufferNum;
public:
	IntFunctionEncoder(){
		eta=6;
		sigma=0;
		beta=0; // linear slope
		alpha =0;
		curDictinctPoolNum = 0;
		readyEncodeBuffer = new Array<int>(3);
		bufferKey = new Array<int>(3);
		//curBufferNum = 0;
		//readyEncodeBuffer = new int[definitionalDomainSize];
		dictinctPool = new int[definitionalDomainSize];
		keyPool = new int[definitionalDomainSize];
	}
	int get_index(int t);
	void addDictionary(int num);
	void encode(int num, ByteArrayOutputStream& baos);
	void flush(ByteArrayOutputStream& baos);
	void calculatelsm(int length, int* x, int* y, int& beta, int& alpha);
};

#endif // !__INTFUNCTIONENCODER__