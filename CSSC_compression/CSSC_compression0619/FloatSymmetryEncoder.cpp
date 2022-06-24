#include "FloatSymmetryEncoder.h"

void FloatSymmetryEncoder::encode(float num, int pos, ByteArrayOutputStream& out) {
    if (pos % 8 == 0 && pos != 0) {
        bit_vector_index++;
    }
    sign_bit_vector[bit_vector_index] <<= 1;
    num -= miu;
    if (num < 0) {
        sign_bit_vector[bit_vector_index] |= 1;
        // num *= -1;
    }
    encoder->encode(num, out);
}

void FloatSymmetryEncoder::flush(ByteArrayOutputStream& out) {
    encoder->flush(out);
}

void FloatSymmetryEncoder::encode_bitvector(ByteArrayOutputStream& out) {
    for (size_t i = 0; i < this->length + 1; i++) {
        out.write(sign_bit_vector[i]);
    }
}