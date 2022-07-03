#include "RleDecoder.h"
/**
 * @brief get header from the byteCache and calculate the mode.
 * @return int header value
 */
int RleDecoder::getHeader()
{
    int header = readUnsignedVarInt(byteCache);
    mode = (header & 1) == 0 ? 0 : 1;
    return header;
}
/**
 * @brief read next number based on the mode specified in header.
 * @details if mode is 0, then read next number by rel, otherwise read next number by bit-packing.
 * @return void
 */
void RleDecoder::readNext()
{
	int header = getHeader();
	switch (mode) {
	case 0:
		currentCount = header >> 1;
		readNumberInRle();
		break;
	case 1:
		callReadBitPackingBuffer(header);
		break;
	}
}
/**
 * @brief prepare for reading bit-packing buffer and call the function that read buffer.
 * @details in last bit-packing group, there may be some useless value; lastBitPackedNum indicates how many values are useful
 * @return void
 */
void RleDecoder::callReadBitPackingBuffer(int header)
{
	int bitPackedGroupCount = header >> 1;
	int lastBitPackedNum = read(byteCache);
	if (bitPackedGroupCount > 0) {
		currentCount =
			(bitPackedGroupCount - 1) * RLE_MIN_REPEATED_NUM + lastBitPackedNum;
		bitPackingNum = currentCount;
	}
	readBitPackingBuffer(bitPackedGroupCount, lastBitPackedNum);
}
/**
 * @brief if buffer has no remaining, returns -1, otherwise read a byte and change to uint8_t.
 * @param buffer
 * @return int
 */
int RleDecoder::read(ByteBuffers& buffer)
{
	if (!buffer.hasRemaining()) {
		return -1;
	}
	return buffer.readuchar() & 0xFF;
}
/**
 * @brief read length and bit width from buffer and byteCache, then initialize the pack.
 * @param buffer
 */
void RleDecoder::readLengthAndBitWidth(ByteBuffer& buffer)
{
	length = readUnsignedVarInt(buffer);
	std::vector<uint8_t> tmp(length);
	buffer.get(tmp, 0, length);
	ByteBuffer tmpbuffer(tmp);
	byteCache = tmpbuffer;
	isLengthAndBitWidthReaded = true;
	bitWidth = read(byteCache);
	initPacker();
}
/**
 * @brief if current count is positive, remaining and next package both exist, return true.
 * @param buffer
 * @return true
 * @return false
 */
bool RleDecoder::hasNext(ByteBuffer& buffer)
{
	if (currentCount > 0 || buffer.remaining() > 0 || hasNextPackage()) {
		return true;
	}
	return false;
}
/**
 * @brief if current count is positive and remaining exists, return true.
 *
 * @param None
 * @return true
 * @return false
 */
bool RleDecoder::hasNextPackage()
{
	return currentCount > 0 || byteCache.remaining() > 0;
}
/**
 * @brief fill the reading buffer with enough zeros.
 * @details if the origin number of byte is bigger than 4, then report the error and return 0.
 * @param buffer
 * @param bitWidth
 * @return int
 */
int RleDecoder::readIntLittleEndianPaddedOnBitWidth(ByteBuffer& buffer, int bitWidth)
{
	int paddedByteNum = (bitWidth + 7) / 8;
	if (paddedByteNum > 4) {
		cout<< "IOException(String.format(TOO_LONG_BYTE_FORMAT, paddedByteNum))"<<endl;
		return 0;
	}
	int result = 0;
	int offset = 0;
	while (paddedByteNum > 0) {
		int ch = read(buffer);
		result += ch << offset;
		offset += 8;
		paddedByteNum--;
	}
	return result;
}
/**
 * @brief read uint8_t from buffer and change to int.
 * @details only remaining exists and the sign bit is not 1 can the data be read.
 * @param buffer
 * @return int
 */
int RleDecoder::readUnsignedVarInt(ByteBuffer& buffer)
{
	int value = 0;
	int i = 0;
	int b = 0;
	while (buffer.hasRemaining() && ((b = buffer.readuchar()) & 0x80) != 0) {
		value |= (b & 0x7F) << i;
		i += 7;
	}
	return value | (b << i);
}
