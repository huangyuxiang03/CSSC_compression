#pragma once
#include "readwriteFile.hpp"
#include <iostream>
#include "IntDeltaEncoder.h"
// #include "IntRleEncoder.h"
#include "ByteArrayOutputStreamV2.h"
#include "ByteBuffer.h"
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
		// std::cout<< "read time: " << read_end - read_beg <<std::endl;
		// com_beg = clock();
		// IntDeltaEncoder encoder;
		// ByteArrayOutputStream out(argv[3], 2 * valueLength * 2);
		// for (int i = 0; i < valueLength; i++) {
		// 	encoder.encode(data[i], out);
		// }
		// com_end = clock();
		// std::cout<< "encode time: " << com_end - com_beg <<std::endl;
		// com_beg = clock();
		// encoder.flush(out);
		// com_end = clock();
		// std::cout<< "flush time: " << com_end - com_beg <<std::endl;
		// out.write2filegzip();
		// com_beg = clock();
		// out.write2file();
		// com_end = clock();
		// std::cout<< "write time: " << com_end - com_beg <<std::endl;

		uint8_t* data1 = new uint8_t[valueLength];
		uint8_t* data2 = new uint8_t[valueLength];
		uint8_t* fake = (uint8_t*)data;
		for (int i = 0; i < valueLength; i++) {
			data1[i] = fake[i * 2];
			data2[i] = fake[i * 2 + 1];
		}
		
		GZIP gzip;
		// uint8_t* cdata = new uint8_t[valueLength*20];
		// int compressedLength = gzip.data_compress((uint8_t*)data, (valueLength)*2, cdata, valueLength*20);
		// writeBinaryFile(argv[3], cdata, compressedLength);

		uint8_t* cdata1 = new uint8_t[valueLength * 20];
		uint8_t* cdata2 = new uint8_t[valueLength * 20];
		int clength1 = gzip.data_compress(data1, valueLength, cdata1, valueLength * 20);
		int clength2 = gzip.data_compress(data2, valueLength, cdata2, valueLength * 20);
		std::cout << "compressed length: " << clength1 + clength2 + 4<< std::endl;
		memcpy(cdata1 + clength1, cdata2, clength2);
		memcpy(cdata1 + clength1 + clength2, &clength2, 4);
		writeBinaryFile(argv[3], cdata1, clength1 + clength2 + 4);
		end = clock();
		std::cout << end - beg << std::endl;
		delete[] data;
		delete[] data1;
		delete[] data2;
		delete[] cdata1;
		delete[] cdata2;
		// delete[] cdata;
		return 0;
	}
	else if (argv[1][0] == 'd') {
		time_t beg, end;
		beg = clock();

		int binaryLength = 0;
		uint8_t* cdata = readBinaryFile(argv[2], binaryLength);
		int clength2;
		memcpy(&clength2, cdata + binaryLength - 4, 4);
		int clength1 = binaryLength - 4 - clength2;
		uint8_t* cdata1 = new uint8_t[clength1];
		memcpy(cdata1, cdata, clength1);
		uint8_t* cdata2 = new uint8_t[clength2];
		memcpy(cdata2, cdata + clength1, clength2);

		GZIP gzip;
		uint8_t* data = new uint8_t[binaryLength*20];
		uint8_t* data1 = new uint8_t[binaryLength*20];
		uint8_t* data2 = new uint8_t[binaryLength*20];
		int temp;
		int dlength1 = gzip.data_decompress(cdata1, clength1, data1, temp);
		int dlength2 = gzip.data_decompress(cdata2, clength2, data2, temp);
		for (int i = 0; i < dlength1; i++) {
			data[2 * i] = data1[i];
			data[2 * i + 1] = data2[i];
		}
		// int deconpressedLength = gzip.data_decompress(cdata, binaryLength, data, temp);
		writeBinaryFile(argv[3], data, 2 * dlength1);
		end = clock();
		std::cout << "total time:" << end - beg << std::endl;
		return 0;
	}
	else {
		return -1;
	}
}