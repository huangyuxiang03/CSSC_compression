#include "FloatEncoder.h"

void FloatEncoder::encode(float f, int pos, ByteArrayOutputStream& out1, ByteArrayOutputStream& out2) {
	int tmp;
	memcpy(&tmp, &f, 4);
	bitvector[pos] = (tmp & (1 << 31)) ? 1 : 0;
	int exponent = 0;
	for (int i = 7; i >= 0; i--) {
		if (tmp & (1 << (i + 23)))
			exponent |= (1 << i);
	}
	exponentEncoder->encode(exponent, out1);
	tmp &= 0x7fffff;
	mantissaEncoder->encode(tmp, out2);
}

void FloatEncoder::flush(ByteArrayOutputStream& out1, ByteArrayOutputStream& out2) {
	exponentEncoder->flush(out1);
	mantissaEncoder->flush(out2);
}

void FloatEncoder::encode_bitvector(ByteArrayOutputStream& out3) {
	int num_byte = length / 8;
	//char* bit_vector_char = new char[num_byte + 1];
	for (int j = 0; j < num_byte; j++) {
		int single_num = 0;
		for (int k = 0; k < 8; k++) {
			single_num = single_num * 2 + bitvector[j * 8 + k];
		}
		std::uint8_t c = single_num;
		//bit_vector_char[j] = c;
		out3.write(c);
	}
	int single_num = 0;
	for (int k = num_byte * 8; k < length; k++) {
		single_num = single_num * 2 + bitvector[k];
	}
	for (int k = 0; k < (num_byte + 1) * 8 - length; k++) {
		single_num *= 2;
	}
	std::uint8_t c = single_num;
	//bit_vector_char[num_byte] = c;
	out3.write(c);
}