#include "BCHDecoder.h"

int BCHDecoder::readInt(int ss, int yyyy, int hhh, int nnn, int www, ByteBuffer& in) {
	if (ss == 0)
		return BCH_63_51(concatenate(yyyy, hhh, nnn, www));
	else
		return decoder.readInt(in);
}

unsigned long long BCHDecoder::concatenate(int Y, int H, int N, int W) {
    unsigned long long res = Y;
    res <<= 11;
    res += H >> 1;
    res <<= 12;
    res += N;
    res <<= 12;
    res += W;
    return res;
}
int BCHDecoder::BCH_63_51(unsigned long long origin) {
    unsigned long long genPoly = 5433;
    unsigned long long fix = 1;
    fix <<= 63;
    origin += fix;
    for (int i = 0; i < 51; i++) {
        unsigned long long base = 1;
        if ((origin & (base << i)) == (base << i))
            origin ^= (genPoly << i);
    }
    return int((origin >> 51) & 0xfff);
}