#include "readFile.hpp"
#include <iostream>
#include "IntDeltaEncoder.h"
#include "ByteArrayOutputStream.h"
#include "GZIP.h"
#include <time.h>


int main(int argc, char* argv[]) {
	if (argc != 4)
		return -1;
	if (argv[1][0] == 'c') {
		time_t beg, end;
		time(&beg);
		int valueLength = 0;
		uint16_t* data = readFile(argv[2], valueLength);
		
		IntDeltaEncoder encoder;
		ByteArrayOutputStream out(argv[3]);
		for (int i = 0; i < valueLength; i++) {
			encoder.encode(data[i], out);
		}
		encoder.flush(out);
		out.write2filegzip();
		time(&end);
		std::cout << "total time:" << end - beg << std::endl;
		return 0;
	}
	else if (argv[1][0] == 'd') {
		return 0;
	}
	else {
		return -1;
	}
}