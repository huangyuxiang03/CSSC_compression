#include "IntRleDecoder.h"
/**
 * @brief if function readInt() return 0, then it returns false, otherwise returns true.
 *
 * @param buffer buffer to read from.
 * @return bool
 */
bool IntRleDecoder::readBoolean(ByteBuffer& buffer)
{
	bool r = readInt(buffer) == 0 ? false : true;
	return r;
}
/**
 * @brief read int value from buffer using rle, if can be read, then returns an integer value based on the current package and count.
 * @param buffer buffer to read from.
 * @return int
 */
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
/**
 * @brief initialize the packer for unpacking int values.
 * @details if packer is not allocated, then allocate it.
 * @param None
 * @return void
 */
void IntRleDecoder::initPacker()
{
    if (packerAllocated)
        delete packer;
    packer = new IntPacker(bitWidth);
    packerAllocated = true;
}
/**
 * @brief read number by integer rle typr.
 * @param None
 * @return void
 */
void IntRleDecoder::readNumberInRle()
{
    currentValue = readIntLittleEndianPaddedOnBitWidth(byteCache, bitWidth);
}
/**
 * @brief read bit-packing buffer and save all int values to currentBuffer.
 * @param bitPackedGroupCount
 * @param lastBitPackedNum
 * @return void
 */
void IntRleDecoder::readBitPackingBuffer(int bitPackedGroupCount, int lastBitPackedNum)
{
    if (currentBufferAllocated)
        delete[] currentBufsfer;
    currentBuffer = new int[bitPackedGroupCount * RLE_MIN_REPEATED_NUM];
    currentBufferAllocated = true;
    vector<std::uint8_t> bytes (bitPackedGroupCount * bitWidth);
    int bytesToRead = bitPackedGroupCount * bitWidth;
    bytesToRead = min(bytesToRead, byteCache.remaining());
    byteCache.get(bytes, 0, bytesToRead);

    packer->unpackAllValues(bytes, bytesToRead, currentBuffer);
}
