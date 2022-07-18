#pragma once
#include "readwriteFile.hpp"
#include <iostream>
#include "IntDeltaEncoder.h"
#include "IntRleEncoder.h"
#include "ByteArrayOutputStreamV2.h"
#include "GZIP.h"
#include <time.h>


int main(int argc, char* argv[]) {

	if (argc != 4)
		return -1;
	if (argv[1][0] == 'c') {
		time_t beg, end;
		time_t read_beg, read_end, write_beg, write_end, com_beg, com_end;
		read_beg = clock();
		beg = clock();
		int valueLength = 0;
		uint16_t* data = readOriginFile(argv[2], valueLength);
		read_end = clock();
		std::cout<< "read time: " << read_end - read_beg <<std::endl;
		com_beg = clock();
		IntDeltaEncoder encoder;
		ByteArrayOutputStream out(argv[3]);
		for (int i = 0; i < valueLength; i++) {
			encoder.encode(data[i], out);
		}
		com_end = clock();
		std::cout<< "encode time: " << com_end - com_beg <<std::endl;
		com_beg = clock();
		encoder.flush(out);
		com_end = clock();
		std::cout<< "flush time: " << com_end - com_beg <<std::endl;
		out.write2filegzip();
		
		// com_beg = clock();
		// out.write2file();
		// com_end = clock();
		// std::cout<< "write time: " << com_end - com_beg <<std::endl;


		
		// com_beg = clock();
		// GZIP gzip;
		// uint8_t* cdata = new uint8_t[valueLength*20];
		// int compressedLength = gzip.data_compress((uint8_t*)data, (valueLength + valueLength/744)*2, cdata, 0);
		// com_end = clock();
		// // std::cout << "compress time: " << com_end - com_beg << std::endl;
		// write_beg = clock();
		// writeBinaryFile(argv[3], cdata, compressedLength);
		// write_end = clock();
		// std::cout << "write time: " << write_end - write_beg << std::endl;
		end = clock();
		std::cout << end - beg << std::endl;
		delete[] data;
		// delete[] cdata;
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