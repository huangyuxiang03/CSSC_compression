#pragma once

#ifndef _GZIP_
#define _GZIP_
//#include <stdio.h>
#include <iostream>
#include <string.h>
//#include <malloc.h>
//using namespace std;
#include "zlib.h"
#include "ByteArrayOutputStream.h"
#pragma comment( lib, "zlibwapi.lib")

class GZIP {
private:

public:
	GZIP() {};
	int data_compress(std::uint8_t* idata, int ilen, std::uint8_t* odata, int& olen);
	int data_decompress(std::uint8_t* idata, int ilen, std::uint8_t* odata, int olen);

};


#endif