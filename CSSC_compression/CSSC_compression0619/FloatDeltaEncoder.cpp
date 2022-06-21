#pragma once
#include "FloatDeltaEncoder.h"

void FloatDeltaEncoder::encode(float v, ByteArrayOutputStream& out) {
	encoder.encode(convertFloatToInt(v), out);
}

void FloatDeltaEncoder::flush(ByteArrayOutputStream& out) {
	encoder.flush(out);
}