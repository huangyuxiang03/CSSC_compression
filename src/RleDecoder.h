#pragma once
#ifndef __RLEDECODER__
#define __RLEDECODER__
#include <iostream>
#include "ByteBuffer.h"

using namespace std;
class RleDecoder {
protected:
	int mode;//!< mode to indicate current encoding type 0 - RLE 1 - BIT_PACKED.
	int bitWidth;//!< bit width for bit-packing and rle to decode.
	int currentCount;//!< number of data left for reading in current buffer.
	int length;//!< how many bytes for all encoded data like [{@code <bitwidth> <encoded-data>}] in inputstream.
	bool isLengthAndBitWidthReaded;//!< a flag to indicate whether current pattern is end. false - need to start reading a new page true - current page isn't over.
	ByteBuffer byteCache;//!< buffer to save data format like [{@code <bitwidth> <encoded-data>}] for decoder.
	int bitPackingNum;//!< number of bit-packing group in which is saved in header.
	int RLE_MIN_REPEATED_NUM;
public:
	RleDecoder() {
		reset();
	}
	void reset() {
		currentCount = 0;
		isLengthAndBitWidthReaded = false;
		bitPackingNum = 0;
		RLE_MIN_REPEATED_NUM = 8;
		//byteCache = ByteBuffer.allocate(0);
	}
	static int readUnsignedVarInt(ByteBuffer& buffer);
	int getHeader();
	void readNext();
	virtual void readNumberInRle(){};
	virtual void readBitPackingBuffer(int bitPackedGroupCount, int lastBitPackedNum){};
	void callReadBitPackingBuffer(int header);
	static int read(ByteBuffer& buffer);
	void readLengthAndBitWidth(ByteBuffer& buffer);
	virtual void initPacker(){};
	bool hasNext(ByteBuffer& buffer);
	bool hasNextPackage();
	static int readIntLittleEndianPaddedOnBitWidth(ByteBuffer& buffer, int bitWidth);
	//int readInt(ByteBuffer& buffer) {};
};

#endif // !__RLEDECODER__