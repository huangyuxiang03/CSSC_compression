#include "IntRleDecoder.h"

bool IntRleDecoder::readBoolean(ByteBuffer& buffer)
{
	bool r = readInt(buffer) == 0 ? false : true;
	return r;
}

int IntRleDecoder::readInt(ByteBuffer& buffer)
{
    
    if (!isLengthAndBitWidthReaded) {
        // start to read a new rle+bit-packing pattern
        readLengthAndBitWidth(buffer);
    }

    if (currentCount == 0) {
        readNext();
    }
    --currentCount;
    int result{0};
    switch (mode) {
    case 0:
        result = currentValue;
        break;
    case 1:
        result = currentBuffer[bitPackingNum - currentCount - 1];
        break;
    }

    if (!hasNextPackage()) {
        isLengthAndBitWidthReaded = false;
    }
    return result;
}

void IntRleDecoder::initPacker()
{
    if (packerAllocated)
        delete packer;
    packer = new IntPacker(bitWidth);
    packerAllocated = true;
}

void IntRleDecoder::readNumberInRle()
{
    currentValue = readIntLittleEndianPaddedOnBitWidth(byteCache, bitWidth);
}

void IntRleDecoder::readBitPackingBuffer(int bitPackedGroupCount, int lastBitPackedNum)
{
    if (currentBufferAllocated)
        delete[] currentBuffer;
    currentBuffer = new int[bitPackedGroupCount * RLE_MIN_REPEATED_NUM];
    currentBufferAllocated = true;
    vector<std::uint8_t> bytes (bitPackedGroupCount * bitWidth);
    int bytesToRead = bitPackedGroupCount * bitWidth;
    bytesToRead = min(bytesToRead, byteCache.remaining());
    byteCache.get(bytes, 0, bytesToRead);

    // save all int values in currentBuffer
    packer->unpackAllValues(bytes, bytesToRead, currentBuffer);
}
