#include "RleDecoder.h"

int RleDecoder::getHeader()
{
    int header = readUnsignedVarInt(byteCache);
    mode = (header & 1) == 0 ? 0 : 1;
    return header;
}

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

void RleDecoder::callReadBitPackingBuffer(int header)
{
	int bitPackedGroupCount = header >> 1;
	// in last bit-packing group, there may be some useless value,
	// lastBitPackedNum indicates how many values is useful
	int lastBitPackedNum = read(byteCache);
	if (bitPackedGroupCount > 0) {
		currentCount =
			(bitPackedGroupCount - 1) * RLE_MIN_REPEATED_NUM + lastBitPackedNum;
		bitPackingNum = currentCount;
	}
	readBitPackingBuffer(bitPackedGroupCount, lastBitPackedNum);
}

int RleDecoder::read(ByteBuffer& buffer)
{
	if (!buffer.hasRemaining()) {
		return -1;
	}
	return buffer.readuchar() & 0xFF;
}

void RleDecoder::readLengthAndBitWidth(ByteBuffer& buffer)
{
	length = readUnsignedVarInt(buffer);
	std::vector<uint8_t> tmp(length);
	buffer.get(tmp, 0, length);
	byteCache = ByteBuffer(tmp);
	isLengthAndBitWidthReaded = true;
	bitWidth = read(byteCache);
	initPacker();
}

bool RleDecoder::hasNext(ByteBuffer& buffer)
{
	if (currentCount > 0 || buffer.remaining() > 0 || hasNextPackage()) {
		return true;
	}
	return false;
}

bool RleDecoder::hasNextPackage()
{
	return currentCount > 0 || byteCache.remaining() > 0;
}

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
