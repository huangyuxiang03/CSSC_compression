/**
 * @file RleEncoder.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-07-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#ifndef __RLEENCODER__
#define __RLEENCODER__
#include <iostream>
#include "ByteArrayOutputStream.h"

using namespace std;


//template <typename T>
/**
 * @brief Encoders using the rle method
 * 
 */
class RleEncoder {
protected:

	int bitWidth{0}; 							//!< The bit width of the data to be encoded
	int repeatCount{0}; 						//!< The number of times the same value is repeated
	int bitPackedGroupCount{0}; 				//!< The number of bit packed groups
	int numBufferedValues{0}; 					//!< The number of values buffered
	vector<vector<std::uint8_t>> bytesBuffer; 	//!< The buffer of bytes to be encoded
	bool isBitPackRun{0}; 						//!< Whether the current run is bit packed

	bool isBitWidthSaved{0}; 					//!< Whether the bit width has been saved
	ByteArrayOutputStream byteCache; 			//!< The cache of bytes to be encoded
	int RLE_MIN_REPEATED_NUM; 					//!< The minimum number of times a value is repeated to be encoded as a run
	int RLE_MAX_BIT_PACKED_NUM; 				//!< The maximum number of values to be encoded as a bit packed run
	int RLE_MAX_REPEATED_NUM; 					//!< The maximum number of times a value is repeated to be encoded as a run

public:
	/**
	 * @brief Construct a new Rle Encoder object
	 * 
	 */
	RleEncoder() {
		isBitPackRun = false;
		isBitWidthSaved = false;

		RLE_MIN_REPEATED_NUM = 8;
		RLE_MAX_BIT_PACKED_NUM = 63;
		RLE_MAX_REPEATED_NUM = 0x7FFF;
	}
	/**
	 * @brief Destroy the Rle Encoder object
	 * 
	 */
	~RleEncoder() {
		vector <vector <std::uint8_t>>().swap(this->bytesBuffer);
		byteCache.reset();
	}
	void reset();								///< Reset the encoder
	void flushrle(ByteArrayOutputStream& out); 	///< flush the rle encoded data to the output stream
	virtual void writeRleRun() {}; 				///< write the rle encoded data to the output stream
	virtual void clearBuffer() {};				///< clear the buffer of bytes to be encoded
	virtual void convertBuffer(){};				///< convert the buffer of bytes to be encoded
	void writeOrAppendBitPackedRun();			///< write the bit packed run to the output stream
	int writeUnsignedVarInt(int value, ByteArrayOutputStream& out);	///< write the unsigned varint to the output stream
	static int numberOfLeadingZeros(int i);		///< get the number of leading zeros of the integer
	static void writeIntLittleEndianPaddedOnBitWidth(int value, ByteArrayOutputStream& out, int bitWidth);///< write the integer to the output stream with little endian and padded on bit width
	void endPreviousBitPackedRun(int lastBitPackedNum);///< end the previous bit packed run

};

#endif // !__RLEENCODER__
