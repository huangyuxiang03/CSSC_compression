/**
 * @file IntRleEncoder.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once
#ifndef __INTRLEENCODER__
#define __INTRLEENCODER__
#include <iostream>
#include "ByteArrayOutputStream.h"
#include "RleEncoder.h"
#include "IntPacker.h"

using namespace std;

class IntRleEncoder : public RleEncoder {
protected:
	vector<int> values; ///< The values to be encoded
	int preValue;		///< The previous value
	int* bufferedValues;///< The buffer of values to be encoded
	IntPacker packer; 	///< The packer to pack the values
public:
	/**
	 * @brief Construct a new Int Rle Encoder object
	 * 
	 */
	IntRleEncoder() {
		bufferedValues = new int[RLE_MIN_REPEATED_NUM];
		preValue = 0;
		//values = new ArrayList<>();
	}
	/**
	 * @brief Destroy the Int Rle Encoder object
	 * 
	 */
	~IntRleEncoder() {
		vector <int>().swap(values);
		delete[] bufferedValues;
	}
	void encode(int value, ByteArrayOutputStream& out);	///< Encode the value
	int getIntMaxBitWidth(vector<int> list);			///< Get the maximum bit width of the list
	void encode(bool value, ByteArrayOutputStream& out);///< Encode the value
	void flush(ByteArrayOutputStream& out);				///< Flush the buffer
	void reset(); 										///< Reset the encoder
	void writeRleRun();									///< Write the rle run
	void clearBuffer();									///< Clear the buffer
	void convertBuffer();								///< Convert the buffer
	void encodeValue(int value);						///<Encode the value
};


#endif // !__INTRLEENCODER__