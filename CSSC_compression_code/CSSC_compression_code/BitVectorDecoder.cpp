#include "BitVectorDecoder.h"

void BitVectorDecoder::encode_bitvector(ByteBuffer& buffer)
{
	int num_byte = length / 8;
	for (int j = 0; j < num_byte; j++) {
		char c = buffer.readByte();
		int single_num = c;
		for (int k = 7; k >= 0; k--) {
			bit_vector[j * 8 + k] = single_num & 1;
			single_num /=  2;
		}
	}
	char c = buffer.readByte();
	int single_num = c;

	for (int k = 0; k < (num_byte + 1) * 8 - length; k++) {
		single_num /= 2;
	}
	for (int k = length - 1;  k > num_byte * 8; k--) {
		bit_vector[k] = single_num & 1;
		single_num /= 2;
	}
}

int BitVectorDecoder::readInt(int j, ByteBuffer& buffer1, ByteBuffer& buffer2)
{
	//if(j%4600==0) 
	//	cout << j << endl;
	//cout << bit_vector[j] << endl;
	if (bit_vector[j] == 1) return decoder1->readInt(buffer1);
	else return decoder2->readInt(buffer2);
}

bool BitVectorDecoder::hasNext(ByteBuffer& buffer1, ByteBuffer& buffer2)
{
	if (decoder1->hasNext(buffer1) || decoder2->hasNext(buffer2))
		return true;
	return false;
}
