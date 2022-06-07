#pragma once
#include <string>
#include <iostream>
//#include <cstdint>
#include <vector>
#include <fstream>
#include "GZIP.h"

using namespace std;

#ifndef __BYTEARRAYOUTPUTSTREAM__
#define __BYTEARRAYOUTPUTSTREAM__

class ByteArrayOutputStream {
private:
	string filepath;
	std::vector<std::uint8_t> bytes;
	//std::uint8_t* compressed_bytes;
	//int olen;
	int* col_pos; // the position of per column data
	int col_n; //the number of remaining column of the ByteArrayOutputStream
	int col_index;
public:
	
	ByteArrayOutputStream() {
		col_n = 0;
		col_index = 0;
	};
	ByteArrayOutputStream(string fp){
		col_n = 0;
		col_index = 0;
		this->filepath = fp;
	};
	ByteArrayOutputStream(std::vector<std::uint8_t> bytes) {
		vector <std::uint8_t>().swap(this->bytes);
		this->bytes.insert(this->bytes.begin(), bytes.begin(), bytes.end());
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
	void readFromFile();
	void writeDatatype(char datatype);
	//void compress();
	std::vector<std::uint8_t> getBytes();
	std::vector<std::uint8_t> getColBytes();
	bool hasNextCol();
	void writeRowCol(int col_n, int* col_pos);
	void reset();
};

#endif // !__BYTEARRAYOUTPUTSTREAM__
