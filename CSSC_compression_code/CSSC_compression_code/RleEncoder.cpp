#pragma once
#include "RleEncoder.h"

void RleEncoder::reset() {
    numBufferedValues = 0;
    repeatCount = 0;
    bitPackedGroupCount = 0;
    bytesBuffer.clear();
    isBitPackRun = false;
    isBitWidthSaved = false;
    byteCache.reset();
}

void RleEncoder::flush(ByteArrayOutputStream& out)
{
    int lastBitPackedNum = numBufferedValues;
	if (repeatCount >= this->RLE_MIN_REPEATED_NUM) {
		writeRleRun();
	}
	else if (numBufferedValues > 0) {
		clearBuffer();
		writeOrAppendBitPackedRun();
		endPreviousBitPackedRun(lastBitPackedNum);
	}
	else {
		endPreviousBitPackedRun(this->RLE_MIN_REPEATED_NUM);
	}
	// write length
	writeUnsignedVarInt(byteCache.getBytes().size(), out);
	out.write(byteCache.getBytes(),0, byteCache.getBytes().size());
	reset();
    //cout << out.getBytes().size() << endl;
}

void RleEncoder::writeOrAppendBitPackedRun()
{
    if (bitPackedGroupCount >= RLE_MAX_BIT_PACKED_NUM) {
        // we've packed as many values as we can for this run,
        // end it and start a new one
        endPreviousBitPackedRun(RLE_MIN_REPEATED_NUM);
    }
    if (!isBitPackRun) {
        isBitPackRun = true;
    }

    convertBuffer();

    numBufferedValues = 0;
    repeatCount = 0;
    ++bitPackedGroupCount;
}

int RleEncoder::writeUnsignedVarInt(int value, ByteArrayOutputStream& out)
{
    int position = 1;
    while ((value & 0xFFFFFF80) != 0L) {
        out.write((value & 0x7F) | 0x80);
        value >>= 7;
        position++;
    }
    out.write(value & 0x7F);
    return position;
}


int RleEncoder::numberOfLeadingZeros(int i)
{
    if (i <= 0)
        return i == 0 ? 32 : 0;
    int n = 31;
    if (i >= 1 << 16) { n -= 16; i >>= 16; }
    if (i >= 1 << 8) { n -= 8; i >>=  8; }
    if (i >= 1 << 4) { n -= 4; i >>=  4; }
    if (i >= 1 << 2) { n -= 2; i >>=  2; }
    return n - (i >> 1);
}

void RleEncoder::writeIntLittleEndianPaddedOnBitWidth(int value, ByteArrayOutputStream& out, int bitWidth)
{
    int paddedByteNum = (bitWidth + 7) / 8;
    if (paddedByteNum > 4) {
        return;
    }
    int offset = 0;
    while (paddedByteNum > 0) {
        out.write((value >> offset) & 0xFF);
        offset += 8;
        paddedByteNum--;
    }
}

void RleEncoder::endPreviousBitPackedRun(int lastBitPackedNum)
{
    if (!isBitPackRun) {
        return;
    }
    std::uint8_t bitPackHeader = (std::uint8_t)((bitPackedGroupCount << 1) | 1);
    byteCache.write(bitPackHeader);
    byteCache.write(lastBitPackedNum);
    for (vector<std::uint8_t> bytes : bytesBuffer) {
        //int len = 0;
        //while (*bytes != NULL) {
        //    bytes++;
        //    len++;
        //}
        byteCache.write(bytes, 0, bytes.size());
    }
    bytesBuffer.clear();
    isBitPackRun = false;
    bitPackedGroupCount = 0;
}
