#include "IntRleEncoder.h"

void IntRleEncoder::encode(int value, ByteArrayOutputStream& out)
{
	values.push_back(value);
}

void IntRleEncoder::encode(bool value, ByteArrayOutputStream& out)
{
    if (value) {
        this->encode(1, out);
    }
    else {
        this->encode(0, out);
    }
}

int IntRleEncoder::getIntMaxBitWidth(vector<int> list)
{
    int maxnum = 1;
    for (int num : list) {
        int bitWidth = 32 - numberOfLeadingZeros(num);
        maxnum = max(bitWidth, maxnum);
    }
    return maxnum;
}

void IntRleEncoder::flush(ByteArrayOutputStream& out)
{
    this->bitWidth = getIntMaxBitWidth(values);
    IntPacker new_packer(bitWidth);
    packer = new_packer;
    for (int value : values) {
        encodeValue(value);
    }
    flushrle(out);
    reset();
}

void IntRleEncoder::reset()
{
    //reset();
    vector <int>().swap(values);
    //values.clear();
    delete[] bufferedValues;
    bufferedValues = new int[RLE_MIN_REPEATED_NUM];
    preValue = 0;
}

void IntRleEncoder::writeRleRun()
{
    endPreviousBitPackedRun(RLE_MIN_REPEATED_NUM);
    writeUnsignedVarInt(repeatCount << 1, byteCache);
    writeIntLittleEndianPaddedOnBitWidth(preValue, byteCache, bitWidth);
    repeatCount = 0;
    numBufferedValues = 0;
}

void IntRleEncoder::clearBuffer()
{
    for (int i = numBufferedValues; i < RLE_MIN_REPEATED_NUM; i++) {
        bufferedValues[i] = 0;
    }
}

void IntRleEncoder::convertBuffer()
{
    vector<std::uint8_t> bytes(bitWidth);

    int* tmpBuffer = new int[RLE_MIN_REPEATED_NUM];
    for (int i = 0; i < RLE_MIN_REPEATED_NUM; i++) {
        tmpBuffer[i] = (int)bufferedValues[i];
    }
    packer.pack8Values(tmpBuffer, 0, bytes);
    // we'll not write bit-packing group to OutputStream immediately
    // we buffer them in list
    bytesBuffer.push_back(bytes);
}

void IntRleEncoder::encodeValue(int value)
{
    if (!isBitWidthSaved) {
        // save bit width in header,
        // perpare for read
        byteCache.write(bitWidth);
        isBitWidthSaved = true;
    }
    if (value==preValue) {
        repeatCount++;
        if (repeatCount >= RLE_MIN_REPEATED_NUM
            && repeatCount <= RLE_MAX_REPEATED_NUM) {
            // value occurs more than RLE_MIN_REPEATED_NUM times but less than
            // EncodingConfig.RLE_MAX_REPEATED_NUM
            // we'll use rle, so just keep on counting repeats for now
            // we'll write current value to OutputStream when we encounter a different value
            return;
        }
        else if (repeatCount == RLE_MAX_REPEATED_NUM + 1) {
            // value occurs more than EncodingConfig.RLE_MAX_REPEATED_NUM
            // we'll write current rle run to stream and keep on counting current value
            repeatCount = RLE_MAX_REPEATED_NUM;
                writeRleRun();
            repeatCount = 1;
            preValue = value;
        }

    }
    else {
        // we encounter a differnt value
        if (repeatCount >= RLE_MIN_REPEATED_NUM) {
            writeRleRun();
        }
        repeatCount = 1;
        preValue = value;
    }
    bufferedValues[numBufferedValues] = value;
    numBufferedValues++;
    // if none of value we encountered occurs more MAX_REPEATED_NUM times
    // we'll use bit-packing
    if (numBufferedValues == RLE_MIN_REPEATED_NUM) {
        writeOrAppendBitPackedRun();
    }
}
