#pragma once

#ifndef __BYTEARRAYOUTPUTSTREAM__
#define __BYTEARRAYOUTPUTSTREAM__

class ByteArrayOutputStream {
private:


public:
	ByteArrayOutputStream();
	ByteArrayOutputStream(int size);
	void write(int b);
	void write(long long b);
	void writeBytes(char b[]);

};

#endif // !__BYTEARRAYOUTPUTSTREAM__
