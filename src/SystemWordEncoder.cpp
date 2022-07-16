#include "SystemWordEncoder.h"

void SystemWordEncoder::encode(int num, ByteArrayOutputStream* out) {
	encoder[count].encode(num, out[count]);
	count = (count + 1) % 288;
}

void SystemWordEncoder::flush(ByteArrayOutputStream* out) {
	for (int i = 0; i < 288; i++) {
		encoder[i].flush(out[i]);
		out[i].addSizeBack();
		if (i != 0) {
			out[0].concatenate(out[i]);
		}
	}
	
}