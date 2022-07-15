#include <cstdio>
#include <iostream>


uint16_t* readFile(char fileName[], int& valueNum) {
	// open file as binary file
	FILE* fp = fopen(fileName, "rb+");

	// calculate the length of bytes
	fseek(fp, 0, SEEK_END);
	int byteLength = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	int valueLength = byteLength / 2; // values are stored in INT16
	valueNum = valueLength;
	uint16_t* data = new uint16_t[valueLength];
	for (int i = 0; i < valueLength; i++) {
		fread(&data[i], 2, 1, fp);
	}
	return data;
}