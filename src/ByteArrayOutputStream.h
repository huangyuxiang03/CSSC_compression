#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include "GZIP.h"

using namespace std;

#ifndef __BYTEARRAYOUTPUTSTREAM__
#define __BYTEARRAYOUTPUTSTREAM__

class ByteArrayOutputStream {
private:
	string filepath;
	string filepath_compresssize;
	std::vector<std::uint8_t> bytes;
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
	ByteArrayOutputStream(std::vector<std::uint8_t> bytes) {
		vector <std::uint8_t>().swap(this->bytes);
		this->bytes.insert(this->bytes.begin(), bytes.begin(), bytes.end());
		dstlength = 0;
	};
	void write(int b);
	void write(long long b);
	void write(char b);
	void write(std::uint8_t b);
	void writeBytes(char b[]);
	void write(char* b, int offset, int len);
	void write(vector<std::uint8_t> b, int offset, int len);
	void write(std::uint8_t* b, int offset, int len);
	void write2file();
	void write2filegzip();
	void readFromFile();
	void writeDatatype(char datatype);
	std::vector<std::uint8_t> getInt();
	std::vector<std::uint8_t> getBytes(); 
	int getCompressedBytesSize();
	std::vector<std::uint8_t> getColBytes();
	std::vector<std::uint8_t> getColBytesGZip();
	std::vector<std::uint8_t> getBytesLength(int length);
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
