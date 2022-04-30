#pragma once

#ifndef _GZIP_
#define _GZIP_
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "zlib.h"
#include "ByteArrayOutputStream.h"

class GZIP {
private:

public:
	GZIP() {};
	int data_compress(Byte *idata, int ilen, Byte *odata, int *olen);
	int data_decompress(Byte *idata, int ilen, Byte *odata, int *olen);

};


#endif