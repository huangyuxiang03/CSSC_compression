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

class GZIP {
private:

public:
	GZIP() {};
	int data_compress(std::uint8_t* idata, int ilen, std::uint8_t* odata, int olen);

	int data_decompress(std::uint8_t* src, int src_size, std::string& dst, int& dst_size);

	

};


#endif