#pragma once
#include <string>
using namespace std;

#ifndef __BYTEARRAYOUTPUTSTREAM__
#define __BYTEARRAYOUTPUTSTREAM__

class ByteArrayOutputStream {
private:
	string filepath;
public:
	
	ByteArrayOutputStream();
	ByteArrayOutputStream(string fp){
		this->filepath = fp;
	};
	void write(int b);
	void write(long long b);
	void writeBytes(char b[]);
	void write(char b[], int offset, int len);
};

#endif // !__BYTEARRAYOUTPUTSTREAM__
