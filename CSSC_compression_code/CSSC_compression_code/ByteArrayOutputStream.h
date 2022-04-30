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
public:
	
	ByteArrayOutputStream(){};
	ByteArrayOutputStream(string fp){
		this->filepath = fp;
	};
	void write(int b);
	void write(long long b);
	void writeBytes(char b[]);
	void write(char b[], int offset, int len);
	void write2file();
};

#endif // !__BYTEARRAYOUTPUTSTREAM__
