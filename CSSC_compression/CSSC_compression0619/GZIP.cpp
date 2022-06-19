#include "GZIP.h"

//idata ��ѹ������
//ilen  ��ѹ�����ݵĳ���
//odata ѹ�������ݴ洢��buffer (Useless now)
int GZIP::data_compress(std::uint8_t*idata, int ilen, std::uint8_t*odata, int olen)
{
    std::string compressed = gzip::compress((char*)idata, ilen);
    memcpy((void*)odata, compressed.data(), compressed.size());
    return compressed.size();
}

//idata ����ѹ����
//ilen  ����ѹ���ݵĳ���
//odata ��ѹ�����ݴ洢��buffer
//olen  ��ѹ���ݴ洢buffer�ĳ���
int GZIP::data_decompress(std::uint8_t* idata, int ilen, std::uint8_t* odata, int& dst_size) {
    std::string decompressed = gzip::decompress((char*)idata, ilen);
    memcpy((void*)odata, decompressed.data(), decompressed.size());
    return decompressed.size();
}