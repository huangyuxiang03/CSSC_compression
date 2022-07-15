#include "GZIP.h"
#include "fast-lzma2.h"
#include <iostream>

//idata ��ѹ������
//ilen  ��ѹ�����ݵĳ���
//odata ѹ�������ݴ洢��buffer (Useless now)
int GZIP::data_compress(std::uint8_t*idata, int ilen, std::uint8_t*odata, int olen)
{
    //int compressed_size = fl2_compress(odata, olen, idata, ilen, fl2_p_compressionlevel);//fl2_p_highcompression);
    //return compressed_size;
    std::string compressed = gzip::compress((char*)idata, ilen);
    memcpy((void*)odata, compressed.data(), compressed.size());
    return compressed.size();
}

//idata ����ѹ����
//ilen  ����ѹ���ݵĳ���
//odata ��ѹ�����ݴ洢��buffer
//olen  ��ѹ���ݴ洢buffer�ĳ���
int GZIP::data_decompress(std::uint8_t* idata, int ilen, uint8_t* odata, int& dst_size) {
    std::cout<<ilen<<" "<<dst_size<<std::endl;
    int decompressed_size = FL2_decompress(odata, dst_size, idata, ilen);
    std::cout<<decompressed_size<<std::endl;
    return decompressed_size;
    /*std::string decompressed = gzip::decompress((char*)idata, ilen);
    odata.resize(decompressed.size());
    memcpy((void*)odata.data(), decompressed.data(), decompressed.size());
    return decompressed.size();*/
}