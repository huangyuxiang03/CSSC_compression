#pragma once
#ifndef _GZIP_
#define _GZIP_
//#include <stdio.h>
#include <iostream>
#include <string.h>
//#include <malloc.h>
//using namespace std;
//#include "zlib.h"
//#include "ByteArrayOutputStream.h"

#include "compress.hpp"
#include "config.hpp"
#include "decompress.hpp"
#include "utils.hpp"
#include "version.hpp"

#pragma comment( lib, "zlibwapi.lib")
using namespace std;
extern int DATA_DECOMPRESSED_POS;
class GZIP {
private:

public:
	GZIP() {};
	int data_compress(std::uint8_t* idata, int ilen, std::uint8_t* odata, int olen) {
		/*std::vector<unsigned char> compressed_data;
		std::string input;
		for (int i = 0; i < ilen; i++) {
			int t = idata[i];
			input += (char)t;
			if ((i+1) % 108 == 0 || i == ilen - 1) {
				std::vector<unsigned char> temp = gzip::compress((unsigned char*)input.data(), input.size());
				compressed_data.insert(compressed_data.end(), temp.begin(), temp.end());
				DATA_DECOMPRESSED_POS = i;
				std::vector<unsigned char> temp_d = gzip::decompress((unsigned char*)temp.data(), temp.size());
				input.clear();
			}
		}*/



		//std::string compressed_data = gzip::compress((char*)idata, ilen);
		//std::string uncompressed = gzip::decompress(compressed_data.data(), compressed_data.size());

		/*memcpy((void*)odata, compressed_data.data(), compressed_data.size());
		return compressed_data.size();*/
		return 0;
	}

	int data_decompress(std::uint8_t* src, int src_size, std::uint8_t* dst, int& dst_size) {
		/*std::string itd;
		for (int i = 0; i < src_size; i++) {
			itd += src[i];
		}
		itd += '\0';
		std::vector<unsigned char> decompressed_data = gzip::decompress((unsigned char*)itd.data(), src_size);
		memcpy((void*)dst, &decompressed_data, decompressed_data.size());
		return decompressed_data.size();*/
		return 0;
	}

	//int data_compress(std::uint8_t* idata, int ilen, std::uint8_t* odata, int olen) {
	//	z_stream z = { 0 };

	//	z.next_in = idata;
	//	z.avail_in = ilen;
	//	z.next_out = odata;
	//	z.avail_out = olen;

	//	cout << "total" << z.avail_in << " bytes" << endl;

	//	/* 使用最高压缩比 */
	//	if (idata && ilen > 0) {
	//		z.zalloc = (alloc_func)0;
	//		z.zfree = (free_func)0;
	//		z.opaque = (voidpf)0;
	//		if (deflateInit(&z, Z_BEST_COMPRESSION) != Z_OK) {
	//			cout << "deflateInit failed!" << endl;
	//			return -1;
	//		}
	//		while (z.avail_in != 0 && z.total_out < olen) {
	//			if (deflate(&z, Z_NO_FLUSH) != Z_OK) {
	//				cout << "deflate Z_NO_FLUSH failed!" << endl;
	//				return -1;
	//			}
	//		}
	//		if (z.avail_in != 0) {
	//			return z.avail_in;
	//		}
	//		for (; ;) {
	//			if (deflate(&z, Z_FINISH) == Z_STREAM_END) break;
	//			if (deflate(&z, Z_FINISH) != Z_STREAM_END) {
	//				cout << "deflate Z_FINISH failed!" << endl;
	//				return -1;
	//			}
	//		}
	//		if (deflateEnd(&z) != Z_OK) {
	//			cout << "deflateEnd failed!" << endl;
	//			return -1;
	//		}
	//		return z.total_out;
	//	}
	//	return 0;
	//}

	//int data_decompress(std::uint8_t* src, int src_size, std::uint8_t* dst, int& dst_size) {
	//	z_stream strm;
	//	strm.zalloc = NULL;
	//	strm.zfree = NULL;
	//	strm.opaque = NULL;

	//	strm.avail_in = src_size;
	//	strm.avail_out = dst_size;
	//	strm.next_in = (std::uint8_t*)src;
	//	strm.next_out = (std::uint8_t*)dst;

	//	int err = -1, ret = -1;
	//	err = inflateInit2(&strm, MAX_WBITS + 16);
	//	if (err == Z_OK) {
	//		err = inflate(&strm, Z_FINISH);
	//		if (err == Z_STREAM_END) {
	//			ret = strm.total_out;
	//		}
	//		else {
	//			inflateEnd(&strm);
	//			return ret;
	//		}
	//	}
	//	else {
	//		inflateEnd(&strm);
	//		return ret;
	//	}
	//	inflateEnd(&strm);
	//	return ret;
	//}

};


#endif