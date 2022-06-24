#include "FloatSymmetryEncoder.h"

vector<int> change_indicies = {2112, 5215, 6963, 9178, 12435, 14889, 17973, 22021, 24778, 27991, 31113, 34084, 36443, 38708, 40849, 43269, 47782, 50449, 52779, 55106, 57823, 59772, 62381, 64591, 67422, 70004, 72154, 74727, 77016, 79368, 81933, 84895, 87222, 90283, 92758, 95290, 98732, 100778, 102874, 104843, 107444, 110583, 113222, 116857, 119205, 121807, 123788, 126162, 128747, 131345, 134832, 137485, 139868, 142620, 144926, 146748, 149153, 151709, 154253, 157724, 160382, 162880, 165095, 167622, 170297, 173074, 175577, 178366, 181622, 184551, 187910, 191126, 194331, 198818, 202765, 206830, 210062, 213482, 216932, 220401, 223690, 226594, 229733, 232929, 235862, 239029, 243386, 246352, 249638, 253008, 256426, 256498, 261716, 264825, 267578, 270349, 273554, 277035, 307102, 337341, 367480, 397606, 427715, 431596, 436363, 440014, 442323, 447831, 451310, 454961, 459106, 462535, 467025, 470548, 473827, 477327, 480172, 482559, 484816, 487099, 489813, 490043, 492720, 492748, 495417, 498032, 501012, 503858, 504047, 507723, 510862, 513547, 515723, 517692};

void FloatSymmetryEncoder::encode(float num, int pos, ByteArrayOutputStream& out) {
    if (binary_search(change_indicies.begin(), change_indicies.end(), pos)) {
        delete encoder;
        encoder = new FloatDeltaEncoder();
        last_value = num;
    }
    encoder->encode(num - last_value, out);
}

void FloatSymmetryEncoder::flush(ByteArrayOutputStream& out) {
    encoder->flush(out);
}

void FloatSymmetryEncoder::encode_bitvector(ByteArrayOutputStream& out) {
    for (size_t i = 0; i < this->length + 1; i++) {
        out.write(sign_bit_vector[i]);
    }
    int a;
    memcpy(&a, &miu, sizeof(int));
    out.write(a);
}