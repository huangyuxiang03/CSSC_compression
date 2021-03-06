#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include "array.h"
#include "GZIP.h"

using namespace std;

#ifndef __BYTEARRAYOUTPUTSTREAMV3__
#define __BYTEARRAYOUTPUTSTREAMV3__

class ByteArrayOutputStream {
private:
	string filepath;
	string filepath_compresssize;
    int length = 0;
    uint8_t* bytes;
	int* col_pos; // the position of per column data
	int col_n; //the number of remaining column of the ByteArrayOutputStream
	int col_index;
	int dstlength;

    int size;
public:
	
	ByteArrayOutputStream(int _size) {
		col_n = 0;
		col_index = 0;
		dstlength = 0;
        size = _size;
        bytes = new uint8_t[_size];
	};
	ByteArrayOutputStream(string fp, int _size){
		col_n = 0;
		col_index = 0;
		this->filepath = fp;
		dstlength = 0;
		filepath_compresssize = "compresssize.csv";
        size = _size;
        bytes = new uint8_t[_size];
	};
	ByteArrayOutputStream(array<std::uint8_t> _bytes) {
        size = _bytes.size();
        bytes = new uint8_t[size];
        memcpy(bytes, _bytes.data(), size);
		dstlength = 0;
	};
    ~ByteArrayOutputStream() {
        delete[] bytes;
    }
	void write(int b);
	void write(long long b);
	void write(char b);
	void write(std::uint8_t b);
	void writeBytes(char b[]);
	void write(char* b, int offset, int len);
	void write(array<std::uint8_t> b, int offset, int len);
	void write(std::uint8_t* b, int offset, int len);
	void write2file();
	void write2filegzip();
	int getCompressedBytesSize();

};

#endif // !__BYTEARRAYOUTPUTSTREAM__
