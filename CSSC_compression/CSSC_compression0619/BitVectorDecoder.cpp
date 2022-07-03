#include "BitVectorDecoder.h"
/**
 * @brief 
 * 
 * @param buffer 
 */
void BitVectorDecoder::decode_bitvector(ByteBuffer& buffer)
{
	int num_byte = length / 8;
	cout<<num_byte<<endl;
	for (int j = 0; j < num_byte; j++) {
		std::uint8_t c = buffer.readuchar();
		int single_num = c;
		for (int k = 7; k >= 0; k--) {
			bit_vector[j * 8 + k] = single_num & 1;
			single_num /=  2;
		}
	}
	std::uint8_t c = buffer.readuchar();
	int single_num = c;

	for (int k = 0; k < (num_byte + 1) * 8 - length; k++) {
		single_num /= 2;
	}
	for (int k = length - 1;  k >= num_byte * 8; k--) {
		bit_vector[k] = single_num & 1;
		single_num /= 2;
	}
}
/**
 * @brief 
 * 
 * @param j 
 * @param buffer1 
 * @param buffer2 
 * @return int 
 */
int BitVectorDecoder::readInt(int j, ByteBuffer& buffer1, ByteBuffer& buffer2)
{
	if (bit_vector[j] == 1) return decoder1->readInt(buffer1);
	else return decoder2->readInt(buffer2);
}
/**
 * @brief 
 * 
 * @param buffer1 
 * @param buffer2 
 * @return true 
 * @return false 
 */
bool BitVectorDecoder::hasNext(ByteBuffer& buffer1, ByteBuffer& buffer2)
{
	if (decoder1->hasNext(buffer1) || decoder2->hasNext(buffer2))
		return true;
	return false;
}
