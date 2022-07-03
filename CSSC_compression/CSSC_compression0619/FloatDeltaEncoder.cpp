#pragma once
#include "FloatDeltaEncoder.h"
/**
 * @brief encode float to buffer
 * 
 * @param v 
 * @param out 
 */
void FloatDeltaEncoder::encode(float v, ByteArrayOutputStream& out) {
	encoder.encode(convertFloatToInt(v), out);
}
/**
 * @brief flush buffer
 * 
 * @param out 
 */
void FloatDeltaEncoder::flush(ByteArrayOutputStream& out) {
	encoder.flush(out);
}