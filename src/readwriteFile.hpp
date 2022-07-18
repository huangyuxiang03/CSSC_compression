#ifndef __READFILE__
#define __READFILE__

#include <cstdio>
#include <iostream>


uint16_t* readOriginFile(char fileName[], int& valueNum) {
	// open file as binary file
	FILE* fp = fopen(fileName, "rb+");

	// calculate the length of bytes
	fseek(fp, 0, SEEK_END);
	int byteLength = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	int valueLength = byteLength / 2; // values are stored in INT16
	valueNum = valueLength;
	uint16_t* data = new uint16_t[valueLength];
	fread(data, 2*valueLength, 1, fp);
	fclose(fp);
	return data;
}

void writeBinaryFile(char fileName[], uint8_t* data, int dataLength) {
	FILE* fp = fopen(fileName, "wb");
	fwrite(data, dataLength, 1, fp);
	fclose(fp);
}

uint8_t* readBinaryFile(char fileName[], int& dataLength) {
	// open file as binary file
	FILE* fp = fopen(fileName, "rb+");

	// calculate the length of bytes
	fseek(fp, 0, SEEK_END);
	int byteLength = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	dataLength = byteLength;
	uint8_t* data = new uint8_t[dataLength];
	fread(data, dataLength, 1, fp);
	fclose(fp);
	return data;
}

#endif