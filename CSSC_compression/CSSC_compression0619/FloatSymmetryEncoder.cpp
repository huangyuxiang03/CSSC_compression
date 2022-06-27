#include "FloatSymmetryEncoder.h"

void FloatSymmetryEncoder::encode(float num, int pos, ByteArrayOutputStream& out) {
    // ->encode(num, out);
    currentSignBit = num < 0;
    if (pos != 0 && pos % 8 == 0) {
        sign_bit_encoder->encode(currentSignBit, out);
    }
    currentSignBit <<= 1;
    currentSignBit += (num < 0);

    num *= -1;
    int intFromFloat = convertFloatToInt(num);

    currentExpBit = intFromFloat >> 23;
    currentValue = intFromFloat & 0xFF;

    exp_encoder->encode(currentExpBit, out);
    value_encoder->encode(currentValue, out);
}

void FloatSymmetryEncoder::flush(ByteArrayOutputStream& out) {
    sign_bit_encoder->flush(out);
    exp_encoder->flush(out);
    value_encoder->flush(out);
}