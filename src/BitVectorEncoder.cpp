#include "BitVectorEncoder.h"

void BitVectorEncoder::encode(int num, int pos, ByteArrayOutputStream& out1, ByteArrayOutputStream& out2)
{
	if (num > mid) {
		encoder1->encode(num, out1);
		bit_vector[pos] = 1;
	} 
	else {
		encoder2->encode(num, out2);
		bit_vector[pos] = 0;
	}
}
void BitVectorEncoder::flush(ByteArrayOutputStream& out1, ByteArrayOutputStream& out2)
{
	encoder1->flush(out1);
	encoder2->flush(out2);
	//for (int i = 0; i < length; i++) {
	//	out2.write((char)bit_vector[i]);
	//}
}

void BitVectorEncoder::encode_bitvector(ByteArrayOutputStream& out3)
{
	int num_byte = length / 8;
	//char* bit_vector_char = new char[num_byte + 1];
	for (int j = 0; j < num_byte; j++) {
		int single_num = 0;
		for (int k = 0; k < 8; k++) {
			single_num = single_num * 2 + bit_vector[j * 8 + k];
		}
		std::uint8_t c = single_num;
		//bit_vector_char[j] = c;
		out3.write(c);
	}
	int single_num = 0;
	for (int k = num_byte*8; k < length; k++) {
		single_num = single_num * 2 + bit_vector[k];
	}
	for (int k = 0; k < (num_byte + 1) * 8 - length; k++) {
		single_num *= 2;
	}
	std::uint8_t c = single_num;
	//bit_vector_char[num_byte] = c;
	out3.write(c);
}
