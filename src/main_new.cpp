#include "readwriteFile.hpp"
#include <iostream>
#include "IntDeltaEncoder.h"
#include "ByteArrayOutputStream.h"
#include "GZIP.h"
#include <time.h>


int main(int argc, char* argv[]) {
	if (argc != 4)
		return -1;
	if (argv[1][0] == 'c') {
		time_t beg, end;
		beg = clock();
		int valueLength = 0;
		uint16_t* data = readOriginFile(argv[2], valueLength);
		std::cout<<"read finish"<<std::endl;
		GZIP gzip;
		uint8_t* cdata = new uint8_t[valueLength*20];
		int compressedLength = gzip.data_compress((uint8_t*)data, valueLength*2, cdata, 0);
		writeBinaryFile(argv[3], cdata, compressedLength);
		end = clock();
		std::cout << "total time:" << end - beg << std::endl;
		delete[] data;
		delete[] cdata;
		return 0;
	}
	else if (argv[1][0] == 'd') {
		time_t beg, end;
		beg = clock();
		int binaryLength = 0;
		uint8_t* cdata = readBinaryFile(argv[2], binaryLength);

		GZIP gzip;
		uint8_t* data = new uint8_t[binaryLength*20];
		int temp;
		int deconpressedLength = gzip.data_decompress(cdata, binaryLength, data, temp);
		writeBinaryFile(argv[3], data, deconpressedLength);
		end = clock();
		std::cout << "total time:" << end - beg << std::endl;
		delete[] cdata;
		delete[] data;
		return 0;
	}
	else {
		return -1;
	}
}