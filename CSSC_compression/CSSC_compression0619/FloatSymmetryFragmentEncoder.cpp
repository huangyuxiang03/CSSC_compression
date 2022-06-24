#include "FloatSymmetryFragmentEncoder.h"

void FloatSymmetryFragmentEncoder::encode(float num, int pos, ByteArrayOutputStream& out) {
    float sig = sqrt(sigma);
    if ((wait_compress_count > MINFRAGMENTLENGTH &&
         (num > miu + 3 * sig || num < miu - 3 * sig)) ||
        wait_compress_count >= MAXFRAGMENTLENGTH) {
        // start encoding
        for (size_t i = 0; i < wait_compress_count; i++) {
            float frag_num = wait_compress[i] - miu;
            encoder->encode(frag_num, out);
        }

        fragment_vector[fragment_vector_count] = pos;
        fragment_miu_vector[fragment_vector_count] = miu;
        fragment_vector_count++;

        wait_compress_count = 0;
        wait_compress = new float[MAXFRAGMENTLENGTH];
        encoder->flush(out);
        encoder = new FloatDeltaEncoder();
    }
    wait_compress[wait_compress_count] = num;
    wait_compress_count++;
    miu = (miu * (wait_compress_count - 1) + num) / wait_compress_count;
    miu_squared = (miu_squared * (wait_compress_count - 1) + num * num) / wait_compress_count;
    if (wait_compress_count > MINFRAGMENTLENGTH - 1) {
        sigma = 0.0f;
        sigma = miu_squared - miu * miu;
    }
}

void FloatSymmetryFragmentEncoder::flush(ByteArrayOutputStream& out) {
    cout << "fragment_vector_count: " << fragment_vector_count << endl;
    encoder->flush(out);
    delete[] fragment_vector;
    delete[] fragment_miu_vector;
    delete[] wait_compress;
    delete encoder;
    fragment_vector = nullptr;
    fragment_miu_vector = nullptr;
    wait_compress = nullptr;
    encoder = nullptr;
}

void FloatSymmetryFragmentEncoder::encode_bitvector(ByteArrayOutputStream& out) {
    for (size_t i = 0; i < this->signed_bit_vector_length; i++) {
        out.write(signed_bit_vector[i]);
    }
    for (int i = 0; i < fragment_vector_count; i++) {
        out.write(fragment_vector[i]);
    }
    for (int i = 0; i < fragment_vector_count; i++) {
        out.write(bitwiseFloatToInt(fragment_miu_vector[i]));
    }
}