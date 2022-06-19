#pragma once
#ifndef _GZIP_
#define _GZIP_
//#include <stdio.h>
#include <iostream>
#include <string.h>
//#include <malloc.h>
//using namespace std;
#include "zlib.h"
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

	int data_decompress(std::uint8_t* src, int src_size, std::uint8_t* dst, int& dst_size) {
		z_stream strm;
		strm.zalloc = NULL;
		strm.zfree = NULL;
		strm.opaque = NULL;

		strm.avail_in = src_size;
		strm.avail_out = dst_size;
		strm.next_in = (std::uint8_t*)src;
		strm.next_out = (std::uint8_t*)dst;

		int err = -1, ret = -1;
		err = inflateInit(&strm, MAX_WBITS);
		
		if (err == Z_OK) {
			err = inflate(&strm, Z_FINISH);
			cout << strm.msg << endl;
			if (err == Z_STREAM_END) {
				ret = strm.total_out;
			}
			else {
				inflateEnd(&strm);
				return ret;
			}
		}
		else {
			inflateEnd(&strm);
			return ret;
		}
		inflateEnd(&strm);
		return ret;
	}

};


#endif