#include "GZIP.h"

//idata ��ѹ������
//ilen  ��ѹ�����ݵĳ���
//odata ѹ�������ݴ洢��buffer
//olen  ѹ�����ݴ洢buffer�ĳ���.
int GZIP::data_compress(std::uint8_t*idata, int ilen, std::uint8_t*odata, int *olen)
{
	z_stream z = { 0 };

	z.next_in = idata;
	z.avail_in = ilen;
	z.next_out = odata;
	z.avail_out = *olen;

	printf("total %u bytes\n", z.avail_in);

	/* ʹ�����ѹ���� */
	if (deflateInit(&z, Z_BEST_COMPRESSION) != Z_OK) {
		printf("deflateInit failed!\n");
		return -1;
	}

	if (deflate(&z, Z_NO_FLUSH) != Z_OK) {
		printf("deflate Z_NO_FLUSH failed!\n");
		return -1;
	}

	if (deflate(&z, Z_FINISH) != Z_STREAM_END) {
		printf("deflate Z_FINISH failed!\n");
		return -1;
	}

	if (deflateEnd(&z) != Z_OK) {
		printf("deflateEnd failed!\n");
		return -1;
	}

	return 0;
}

//idata ����ѹ����
//ilen  ����ѹ���ݵĳ���
//odata ��ѹ�����ݴ洢��buffer
//olen  ��ѹ���ݴ洢buffer�ĳ���
int GZIP::data_decompress(std::uint8_t* idata, int ilen, std::uint8_t* odata, int *olen)
{
	z_stream z = { 0 };

	z.next_in = idata;
	z.avail_in = ilen;
	z.next_out = odata;
	z.avail_out = *olen;

	if (inflateInit(&z) != Z_OK) {
		printf("inflateInit failed!\n");
		return -1;
	}

	if (inflate(&z, Z_NO_FLUSH) != Z_STREAM_END) {
		printf("inflate Z_NO_FLUSH failed!\n");
		return -1;
	}

	if (inflate(&z, Z_FINISH) != Z_STREAM_END) {
		printf("inflate Z_FINISH failed!\n");
		return -1;
	}

	if (inflateEnd(&z) != Z_OK) {
		printf("inflateEnd failed!\n");
		return -1;
	}

	printf("decompressed data: %s\n", odata);
	return 0;
}