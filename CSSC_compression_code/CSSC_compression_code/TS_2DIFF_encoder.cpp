#pragma once
#include "TS_2DIFF_encoder.h"
#include <corecrt_math.h>

TS_2DIFF_encoder::TS_2DIFF_encoder(int size) :
	blockSize(size) { }

void TS_2DIFF_encoder::writeDataWithMinWidth() {
	for (int i = 0; i < writeIndex; i++) {
		writeValueToBytes(i);
	}
	int encodingLength = (int)(ceil(((double)(writeIndex * writeWidth) / 8.0)));
	out.write(encodingBlockBuffer, 0, encodingLength);
}

void TS_2DIFF_encoder::writeHeaderToBytes() {
	out.write(writeIndex);
	out.write(writeWidth);
	writeHeader();
}

void TS_2DIFF_encoder::flushBlockBuffer(ByteArrayOutputStream out) {
	if (writeIndex == -1)
		return;
	this->out = out;
	for (int i = 0; i < writeIndex; i++)
		calcTwoDiff(i);
	writeWidth = calculateBitWidthsForDeltaBlockBuffer();
	writeHeaderToBytes();
	writeDataWithMinWidth();

	reset();
	writeIndex = -1;
}

void TS_2DIFF_encoder::flush(ByteArrayOutputStream out) {
	flushBlockBuffer(out);
}