#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include "array.h"
#include "GZIP.h"

using namespace std;

#ifndef __BYTEARRAYOUTPUTSTREAMV2__
#define __BYTEARRAYOUTPUTSTREAMV2__

class ByteArrayOutputStream {
private:
	string filepath;
	string filepath_compresssize;
	array<std::uint8_t> bytes;
	int* col_pos; // the position of per column data
	int col_n; //the number of remaining column of the ByteArrayOutputStream
	int col_index;
	int dstlength;
public:
	
	ByteArrayOutputStream() {
		col_n = 0;
		col_index = 0;
		dstlength = 0;
	};
	ByteArrayOutputStream(string fp){
		col_n = 0;
		col_index = 0;
		this->filepath = fp;
		dstlength = 0;
		filepath_compresssize = "compresssize.csv";
	};
	ByteArrayOutputStream(array<std::uint8_t> bytes) {
		array <std::uint8_t>().swap(this->bytes);
		this->bytes.insert(this->bytes.begin(), bytes.begin(), bytes.end());
		dstlength = 0;
	};
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
	void readFromFile();
	void writeDatatype(char datatype);
	array<std::uint8_t> getInt();
	array<std::uint8_t> getBytes(); 
	int getCompressedBytesSize();
	array<std::uint8_t> getColBytes();
	array<std::uint8_t> getColBytesGZip();
	array<std::uint8_t> getBytesLength(int length);
	bool hasNextCol();
	void writeRowCol(int col_n, int* col_pos);
	void reset();

	void addSizeBack();
	void concatenate(ByteArrayOutputStream& b);
	int remaining() {
		return bytes.size();
	}
};

#endif // !__BYTEARRAYOUTPUTSTREAM__
