#include "IndexDecoder.h"
/**
 * @brief 
 * 
 * @param count 
 */
void IndexDecoder::setBit_vector0_count(int count)
{
	bit_vector0_count = count;
}
/**
 * @brief 
 * 
 * @param buffer 
 */
void IndexDecoder::decode_bitvector(ByteBuffer& buffer)
{
	int num_byte = bit_vector0_count / 8;
	for (int j = 0; j < num_byte; j++) {
		std::uint8_t c = buffer.readuchar();
		int single_num = c;
		for (int k = 7; k >= 0; k--) {
			bit_vector0[j * 8 + k] = single_num & 1;
			single_num /= 2;
		}
	}
	std::uint8_t c = buffer.readuchar();
	int single_num = c;

	for (int k = 0; k < (num_byte + 1) * 8 - bit_vector0_count; k++) {
		single_num /= 2;
	}
	for (int k = bit_vector0_count - 1; k >= num_byte * 8; k--) {
		bit_vector0[k] = single_num & 1;
		single_num /= 2;
	}
}
/**
 * @brief 
 * 
 * @param array 
 * @param buffer 
 */
void IndexDecoder::readInt(vector<int>& array, ByteBuffer& buffer)
{
	int j = 0;
	for (int i = 0; i < bit_vector0_count; i++) {
		if (bit_vector0[i] == 0) {
			for (int k = 0; k < 256; k++) {
				array.push_back(k);
			}
		}
		else if (bit_vector0[i] == 1) {
			int bvn = buffer.readuchar();
			for (int k = 0; k < bvn; k++) {
				array.push_back(k);
			}
			j++;
		}
	}
}

