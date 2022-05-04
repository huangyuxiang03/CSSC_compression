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
	int colnum{1};
	std::vector<int>bytesnum;
public:
	
	ByteArrayOutputStream(){};
	ByteArrayOutputStream(string fp){
		this->filepath = fp;
	};
	void setFilePath(string fp) {
		this->filepath = fp;
	}
	void concatenate(ByteArrayOutputStream& b) {
		bytesnum.push_back(bytes.size());
		bytes.insert(bytes.end(), b.bytes.begin(), b.bytes.end());
		colnum += b.colnum;
	}
	void saveSize() {
		bytesnum.push_back(bytes.size());
	}
	ByteArrayOutputStream(std::vector<std::uint8_t> bytes) {
		vector <std::uint8_t>().swap(this->bytes);
		this->bytes.insert(this->bytes.begin(), bytes.begin(), bytes.end());
	};
	void write(int b);
	void write(long long b);
	void writeBytes(char b[]);
	void write(char* b, int offset, int len);
	void write2file();
	std::vector<std::uint8_t> getBytes();
};

#endif // !__BYTEARRAYOUTPUTSTREAM__
