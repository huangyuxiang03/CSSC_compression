#pragma once
#include "ByteBuffer.h"
#include "TS_2DIFF_decoder.h"
#ifndef __INTLONGDELTADECODER__
#define __INTLONGDELTADECODER__
#define ll long long

class IntDeltaDecoder : public TS_2DIFF_decoder {
private:
	int firstValue;						//!< first value of delta
	int* data;							//!< data array
	int previous;						//!< previous value of delta
	int minDeltaBase;					//!< min delta base
	bool dataArrayAllocated = false;	//!< data array allocated
	bool deltaBufAllocated = false;		//!< delta buffer allocated
public:
	int readT(ByteBuffer& buffer);
	int loadIntBatch(ByteBuffer& buffer);
	void readPack();
	int readInt(ByteBuffer& buffer);
	void readHeader(ByteBuffer& buffer);
	void allocateDataArray();
	void readValue(int i);
	void reset() { }
	~IntDeltaDecoder();
};

#endif // !__LONGDELTADECODER__
