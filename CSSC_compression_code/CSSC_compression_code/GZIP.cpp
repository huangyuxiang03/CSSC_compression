#include "GZIP.h"

//idata 待压缩数据
//ilen  待压缩数据的长度
//odata 压缩后数据存储的buffer
//olen  压缩数据存储buffer的长度.
int GZIP::data_compress(std::uint8_t*idata, int ilen, std::uint8_t*odata, int& olen)
{
	z_stream z = { 0 };

	z.next_in = idata;
	z.avail_in = ilen;
	z.next_out = NULL;
	z.avail_out = 0;

	cout << "total" << z.avail_in<<" bytes" << endl;

	/* 使用最高压缩比 */
	if (deflateInit(&z, Z_BEST_COMPRESSION) != Z_OK) {
		cout << "deflateInit failed!" << endl;
		return -1;
	}

	if (deflate(&z, Z_NO_FLUSH) != Z_OK) {
		cout << "deflate Z_NO_FLUSH failed!" << endl;
		return -1;
	}

	if (deflate(&z, Z_FINISH) != Z_STREAM_END) {
		cout << "deflate Z_FINISH failed!" << endl;
		return -1;
	}

	if (deflateEnd(&z) != Z_OK) {
		cout << "deflateEnd failed!" << endl;
		return -1;
	}
	delete[] odata;
	odata = z.next_out;
	olen = z.avail_out;

	return 0;
}

//idata 待解压数据
//ilen  待解压数据的长度
//odata 解压后数据存储的buffer
//olen  解压数据存储buffer的长度
int GZIP::data_decompress(std::uint8_t* idata, int ilen, std::uint8_t* odata, int olen)
{
	z_stream z = { 0 };

	z.next_in = idata;
	z.avail_in = ilen;
	z.next_out = odata;
	z.avail_out = olen;

	if (inflateInit(&z) != Z_OK) {
		cout << "inflateInit failed!" << endl;
		return -1;
	}

	if (inflate(&z, Z_NO_FLUSH) != Z_STREAM_END) {
		cout << "inflate Z_NO_FLUSH failed!" << endl;
		return -1;
	}

	if (inflate(&z, Z_FINISH) != Z_STREAM_END) {
		cout << "inflate Z_FINISH failed!" << endl;
		return -1;
	}

	if (inflateEnd(&z) != Z_OK) {
		cout << "inflateEnd failed!" << endl;
		return -1;
	}

	cout << "decompressed data:"<< odata << endl;
	return 0;
}