#include "GZIP.h"

//idata 待压缩数据
//ilen  待压缩数据的长度
//odata 压缩后数据存储的buffer (Useless now)
int GZIP::data_compress(std::uint8_t*idata, int ilen, std::uint8_t*odata, int olen)
{
    std::string compressed = gzip::compress((char*)idata, ilen);
    memcpy((void*)odata, compressed.data(), compressed.size());
    return compressed.size();
}

//idata 待解压数据
//ilen  待解压数据的长度
//odata 解压后数据存储的buffer
//olen  解压数据存储buffer的长度
int GZIP::data_decompress(std::uint8_t* idata, int ilen, std::uint8_t* odata, int& dst_size) {
    std::string decompressed = gzip::decompress((char*)idata, ilen);
    memcpy((void*)odata, decompressed.data(), decompressed.size());
    return decompressed.size();
}