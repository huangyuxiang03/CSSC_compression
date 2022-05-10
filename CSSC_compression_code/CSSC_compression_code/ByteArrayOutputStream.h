#pragma once
#include <string>
#include <iostream>
//#include <cstdint>
#include <vector>
#include <fstream>
using namespace std;

#ifndef __BYTEARRAYOUTPUTSTREAM__
#define __BYTEARRAYOUTPUTSTREAM__

class ByteArrayOutputStream {
private:
	string filepath;
	std::vector<std::uint8_t> bytes;
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
	void writeBytes(char b[]);
	void write(char* b, int offset, int len);
	void write2file();
	void readFromFile();
	std::vector<std::uint8_t> getBytes();
	std::vector<std::uint8_t> getColBytes();
	bool hasNextCol();
	void writeRowCol(int col_n, int* col_pos);
};

#endif // !__BYTEARRAYOUTPUTSTREAM__
