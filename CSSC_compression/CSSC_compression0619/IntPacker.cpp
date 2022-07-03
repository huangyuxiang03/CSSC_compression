#include "IntPacker.h"
/**
 * @brief 
 * 
 * @param values 
 * @param offset 
 * @param buf 
 */
void IntPacker::pack8Values(int* values, int offset, vector<std::uint8_t>& buf)
{
    int bufIdx = 0;
    int valueIdx = offset;
    // remaining bits for the current unfinished Integer
    int leftBit = 0;

    while (valueIdx < NUM_OF_INTS + offset) {
        // buffer is used for saving 32 bits as a part of result
        int buffer = 0;
        // remaining size of bits in the 'buffer'
        int leftSize = 32;

        // encode the left bits of current Integer to 'buffer'
        if (leftBit > 0) {
            buffer |= (values[valueIdx] << (32 - leftBit));
            leftSize -= leftBit;
            leftBit = 0;
            valueIdx++;
        }

        while (leftSize >= width && valueIdx < NUM_OF_INTS + offset) {
            // encode one Integer to the 'buffer'
            buffer |= (values[valueIdx] << (leftSize - width));
            leftSize -= width;
            valueIdx++;
        }
        // If the remaining space of the buffer can not save the bits for one Integer,
        if (leftSize > 0 && valueIdx < NUM_OF_INTS + offset) {
            // put the first 'leftSize' bits of the Integer into remaining space of the
            // buffer
            buffer |= (values[valueIdx] >> (width - leftSize));
            leftBit = width - leftSize;
        }

        // put the buffer into the final result
        for (int j = 0; j < 4; j++) {
            buf[bufIdx] = (std::uint8_t)((buffer >> ((3 - j) * 8)) & 0xFF);
            bufIdx++;
            if (bufIdx >= width) {
                return;
            }
        }
    }
}

/**
 * @brief 
 * 
 * @param buf 
 * @param offset 
 * @param values 
 */
void IntPacker::unpack8Values(vector<std::uint8_t>& buf, int offset, int* values)
{
    int byteIdx = offset;
    unsigned long long buffer = 0;
    // total bits which have read from 'buf' to 'buffer'. i.e.,
    // number of available bits to be decoded.
    int totalBits = 0;
    int valueIdx = 0;

    while (valueIdx < NUM_OF_INTS) {
        // If current available bits are not enough to decode one Integer,
        // then add next byte from buf to 'buffer' until totalBits >= width
        while (totalBits < width) {
            buffer = (buffer << 8) | (buf[byteIdx] & 0xFF);
            byteIdx++;
            totalBits += 8;
        }

        // If current available bits are enough to decode one Integer,
        // then decode one Integer one by one until left bits in 'buffer' is
        // not enough to decode one Integer.
        while (totalBits >= width && valueIdx < 8) {
            values[valueIdx] = (int)(buffer >> (totalBits - width));
            valueIdx++;
            totalBits -= width;
            buffer = buffer & ((1 << totalBits) - 1);
        }
    }
}
/**
 * @brief 
 * 
 * @param buf 
 * @param length 
 * @param values 
 */
void IntPacker::unpackAllValues(vector<std::uint8_t>& buf, int length, int* values)
{
    int idx = 0;
    int k = 0;
    while (idx < length) {
        int* tv = new int[8];
        // decode 8 values one time, current result will be saved in the array named 'tv'
        unpack8Values(buf, idx, tv);
        for (int i = 0; i < 8; i++) {
            values[i + k] = tv[i];
        }
        //System.arraycopy(tv, 0, values, k, 8);
        idx += width;
        k += 8;
    }
}
/**
 * @brief 
 * 
 * @param width 
 */
void IntPacker::setWidth(int width)
{
    this->width = width;
}
