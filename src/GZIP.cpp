#include "GZIP.h"
#include "fast-lzma2.h"
#include <iostream>

int GZIP::data_compress(std::uint8_t*idata, int ilen, std::uint8_t*odata, int olen)
{
    // int compressed_size = FL2_compress(odata, olen, idata, ilen, 1);//fl2_p_highcompression);
    // return compressed_size;
    return gzip::fast_compress((char*)idata, odata, ilen,6);

    // std::string compressed = gzip::compress((char*)idata, ilen);
    // memcpy((void*)odata, compressed.data(), compressed.size());
    // return compressed.size();
}


int GZIP::data_decompress(std::uint8_t* idata, int ilen, uint8_t* odata, int& dst_size) {
    // std::cout<<ilen<<" "<<dst_size<<std::endl;
    // int decompressed_size = FL2_decompress(odata, dst_size, idata, ilen);
    // std::cout<<decompressed_size<<std::endl;
    // return decompressed_size;

    // return 0;

    std::string decompressed = gzip::decompress((char*)idata, ilen);
    memcpy((void*)odata, decompressed.data(), decompressed.size());
    return decompressed.size();
}