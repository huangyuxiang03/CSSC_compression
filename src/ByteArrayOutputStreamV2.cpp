#include "ByteArrayOutputStreamV2.h"

void ByteArrayOutputStream::write(int b){
    memcpy(bytes + length, &b, 4);
    length += 4;
}

void ByteArrayOutputStream::write(long long b){
    memcpy(bytes + length, &b, 8);
    length += 8;
}

void ByteArrayOutputStream::write(char b)
{
    memcpy(bytes + length, &b, 1);
    length += 1;
}

void ByteArrayOutputStream::write(std::uint8_t b)
{
    memcpy(bytes + length, &b, 1);
    length += 1;
}

void ByteArrayOutputStream::writeBytes(char b[]){
	int len = sizeof(b);
    memcpy(bytes + length, &b, len);
    length += len;
}

void ByteArrayOutputStream::write(char* b, int offset, int len)
{
	int end = offset + len;
	for (int i=offset; i < end; i++) {
        memcpy(bytes + length, &b[len - i - 1], 1);
        length += 1;
	}
	//delete[] b;
}
void ByteArrayOutputStream::write(array<std::uint8_t> b, int offset, int len)
{
	int end = offset + len;
    memcpy(bytes + length, b.begin(), len);
    length += len;
	// array <std::uint8_t>().swap(b);
}
void ByteArrayOutputStream::write(std::uint8_t* b, int offset, int len)
{
	int end = offset + len;
    memcpy(bytes + length, b + offset, len);
    length += len;
	//delete[] b;
}

void ByteArrayOutputStream::write2file()
{  
    FILE* fp = fopen((char*)this->filepath.c_str(), "wb");
    fwrite(bytes, length, 1, fp);
    fclose(fp);
}

void ByteArrayOutputStream::write2filegzip()
{
	int olen=0;
    int ilen = length;
    GZIP gzip;
    std::uint8_t* compressed_bytes = new std::uint8_t[ilen*2];
    olen = gzip.data_compress(bytes, ilen, compressed_bytes, ilen*2);

    cout << "ilen: " << ilen << endl;
    cout << "olen: " << olen << endl;
    dstlength = olen;
    
    
    FILE* fp = fopen((char*)this->filepath.c_str(), "wb");
    fwrite(compressed_bytes, dstlength, 1, fp);
    fclose(fp);
    
    delete[] compressed_bytes;	
}

int ByteArrayOutputStream::getCompressedBytesSize()
{
	return dstlength;
}
