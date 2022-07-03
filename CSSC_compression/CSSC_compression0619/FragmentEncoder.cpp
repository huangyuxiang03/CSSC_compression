#include "FragmentEncoder.h"
/**
 * @brief Encode a float.
 * 
 * @param num  The float to encode.
 * @param pos  The position of the float in the array.
 * @param out  The output stream.
 */
void FragmentEncoder::encode(float num, int pos, ByteArrayOutputStream& out)
{
	float sig = sqrt(sigma);
	if ((wait_compress_count > MINFRAGMENTLENGTH &&
		(num > miu + 3*sig || num < miu - 3*sig))||
		wait_compress_count >= MAXFRAGMENTLENGTH){
		fragment_vector[fragment_vector_count] = pos;
		fragment_vector_count++;
		wait_compress_count = 0;
		wait_compress = new float[10000];
		encoder->flush(out);
		encoder = new FloatDeltaEncoder();
	}		
	wait_compress[wait_compress_count] = num;
	wait_compress_count++;
	encoder->encode(num, out);
	miu = (miu * (wait_compress_count - 1) + num) / wait_compress_count;
	square_miu = (square_miu * (wait_compress_count - 1) + num * num) / wait_compress_count;
	if (wait_compress_count > MINFRAGMENTLENGTH -1) {
		sigma = 0.0f;
		sigma = square_miu - miu * miu;
	}
	//miu = miu_i[pos];
}
/**
 * @brief Flush the encoder.
 * 
 * @param out  The output stream.
 */
void FragmentEncoder::flush(ByteArrayOutputStream& out)
{
	cout << "fragment_vector_count: " << fragment_vector_count << endl;
	encoder->flush(out);
	reset(0, MAXFRAGMENTLENGTH);
}
/**
 * @brief encode the bitvector
 * 
 * @param out  the output stream
 */
void FragmentEncoder::encode_bitvector(ByteArrayOutputStream& out)
{
	for (int i = 0; i < fragment_vector_count; i++) {
		out.write(fragment_vector[i]);
	}
}
/**
 * @brief reset the encoder.
 * 
 * @param miu  the miu of the encoder.
 * @param length  the length of the encoder.
 */
void FragmentEncoder::reset(float miu, int length)//
{
	this->miu = miu;
	this->square_miu = miu * miu;
	this->sigma = 0.0f;
	delete[] fragment_vector;
	delete[] wait_compress;
	fragment_vector = new int[length / MINFRAGMENTLENGTH];
	wait_compress = new float[MAXFRAGMENTLENGTH];
	fragment_vector_count = 0;
	wait_compress_count = 0;
	encoder = new FloatDeltaEncoder();
}
