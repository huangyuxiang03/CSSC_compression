#include "IndexEncoder.h"

void IndexEncoder::encode(int num, ByteArrayOutputStream& out)
{
	increase_count++;
	if (num - prevalue != 1) {
		if (increase_count == 256) {
			bit_vector0[bit_vector0_count] = 0;
		}
		else {
			bit_vector0[bit_vector0_count] = 1;
			bit_vector1_num[bit_vector1_num_count] = increase_count;
			bit_vector1_num_count++;
		}
		// one cycle
		bit_vector0_count++;
		increase_count = 0;
	}
	prevalue = num;
}

void IndexEncoder::encode_bitvector(ByteArrayOutputStream& out)
{
	int num_byte = bit_vector0_count / 8;
	for (int j = 0; j < num_byte; j++) {
		int single_num = 0;
		for (int k = 0; k < 8; k++) {
			single_num = single_num * 2 + bit_vector0[j * 8 + k];
		}
		std::uint8_t c = single_num;
		out.write(c);
	}
	int single_num = 0;
	for (int k = num_byte * 8; k < bit_vector0_count; k++) {
		single_num = single_num * 2 + bit_vector0[k];
	}
	for (int k = 0; k < (num_byte + 1) * 8 - bit_vector0_count; k++) {
		single_num *= 2;
	}
	std::uint8_t c = single_num;
	out.write(c);
}

void IndexEncoder::flush(ByteArrayOutputStream& out)
{
	if (increase_count == 255) {
		bit_vector0[bit_vector0_count] = 0;
	}
	else {
		bit_vector0[bit_vector0_count] = 1;
		increase_count++;
		bit_vector1_num[bit_vector1_num_count] = increase_count;
		bit_vector1_num_count++;
	}
	bit_vector0_count++;
	increase_count = 0;
	out.write(bit_vector0_count);
	
	encode_bitvector(out);
	for (int i = 0; i < bit_vector1_num_count; i++) {
		out.write(bit_vector1_num[i]);
	}
	bit_vector0_count = 0;
	delete[] bit_vector1_num;
	delete[] bit_vector0;
}

int IndexEncoder::getBit_vector1_num_count()
{
	return bit_vector1_num_count;
}
