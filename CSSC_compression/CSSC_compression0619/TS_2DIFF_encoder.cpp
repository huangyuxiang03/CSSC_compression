#pragma once
#include "TS_2DIFF_encoder.h"
#include <cmath>

TS_2DIFF_encoder::TS_2DIFF_encoder(int size) :
	blockSize(size) { }

void TS_2DIFF_encoder::writeDataWithMinWidth(ByteArrayOutputStream& out) {
	for (int i = 0; i < writeIndex; i++) {
		writeValueToBytes(i);
	}
	int encodingLength = (int)(ceil(((double)(writeIndex * writeWidth) / 8.0)));
	out.write(encodingBlockBuffer, 0, encodingLength);
}

void TS_2DIFF_encoder::writeHeaderToBytes(ByteArrayOutputStream& out) {
	out.write(writeIndex);
	//cout << writeIndex << endl;
	out.write(writeWidth);
	writeHeader(out);
}

void TS_2DIFF_encoder::flushBlockBuffer(ByteArrayOutputStream &out) {
	if (writeIndex == -1)
		return;
	for (int i = 0; i < writeIndex; i++)
		calcTwoDiff(i);
	writeWidth = calculateBitWidthsForDeltaBlockBuffer();
	writeHeaderToBytes(out);
	writeDataWithMinWidth(out);

	reset();
	writeIndex = -1;
}

void TS_2DIFF_encoder::flush(ByteArrayOutputStream &out) {
	flushBlockBuffer(out);
}

int TS_2DIFF_encoder::BLOCK_DEFAULT_SIZE = 4096;