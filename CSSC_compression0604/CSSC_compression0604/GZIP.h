#pragma once
#ifndef _GZIP_
#define _GZIP_
#include <stdio.h>
#include <iostream>
#include <string.h>
//#include <malloc.h>
//using namespace std;
//#include "zlib.h"
#include "../../CSSC_compression_code/CSSC_compression_code/zlib.h"
//#include "ByteArrayOutputStream.h"
#pragma comment( lib, "zlibwapi.lib")
using namespace std;
class GZIP {
private:

public:
	GZIP() {};
	int data_compress(std::uint8_t* idata, int ilen, std::uint8_t* odata, int olen) {
		z_stream z = { 0 };

		z.next_in = idata;
		z.avail_in = ilen;
		z.next_out = odata;
		z.avail_out = olen;

		cout << "total" << z.avail_in << " bytes" << endl;

		/* 使用最高压缩比 */
		if (idata && ilen > 0) {
			z.zalloc = (alloc_func)0;
			z.zfree = (free_func)0;
			z.opaque = (voidpf)0;
			if (deflateInit(&z, Z_BEST_COMPRESSION) != Z_OK) {
				cout << "deflateInit failed!" << endl;
				return -1;
			}
			while (z.avail_in != 0 && z.total_out < olen) {
				if (deflate(&z, Z_NO_FLUSH) != Z_OK) {
					cout << "deflate Z_NO_FLUSH failed!" << endl;
					return -1;
				}
			}
			if (z.avail_in != 0) {
				return z.avail_in;
			}
			for (; ;) {
				if (deflate(&z, Z_FINISH) == Z_STREAM_END) break;
				if (deflate(&z, Z_FINISH) != Z_STREAM_END) {
					cout << "deflate Z_FINISH failed!" << endl;
					return -1;
				}
			}
			if (deflateEnd(&z) != Z_OK) {
				cout << "deflateEnd failed!" << endl;
				return -1;
			}
			return z.total_out;
		}
		return 0;
	}

	int data_decompress(std::uint8_t* idata, int ilen, std::uint8_t* odata, int olen) {
		z_stream z = { 0 };
		z.zalloc = NULL;
		z.zfree = NULL;
		z.opaque = NULL;

		z.next_in = idata;
		z.avail_in = ilen;
		z.next_out = odata;
		z.avail_out = olen;

		int err = inflateInit2(&z, MAX_WBITS + 16);
		int ret = 0;
		if (err == Z_OK) {
			err = inflate(&z, Z_FINISH);
			if (err = Z_STREAM_END) {
				ret = z.total_out;
			}
			else {
				inflateEnd(&z);
				return err;
			}
		}
		else {
			inflateEnd(&z);
			return err;
		}
		inflateEnd(&z);
		//cout << "decompressed data:" << odata << endl;
		return ret;
	}

};


#endif