#pragma once
#include "ByteArrayOutputStream.h"

template <typename T>
std::vector<std::uint8_t> ToByte(T input)
{
	std::uint8_t* bytePointer = reinterpret_cast<std::uint8_t*>(&input);
	return std::vector<std::uint8_t>(bytePointer, bytePointer + sizeof(T));
}

void ByteArrayOutputStream::write(int b){
   std::vector<std::uint8_t> bytes_tmp = ToByte(b);
   this->bytes.insert(this->bytes.end(),bytes_tmp.begin(),bytes_tmp.end());

}
void ByteArrayOutputStream::write(long long b){
   std::vector<std::uint8_t> bytes_tmp = ToByte(b);
   this->bytes.insert(this->bytes.end(),bytes_tmp.begin(),bytes_tmp.end());
}
void ByteArrayOutputStream::writeBytes(char b[]){
	int len = sizeof(b);
	for (int i=0; i < len;i++) {
		std::vector<std::uint8_t> byte_tmp = ToByte(b[len - i - 1]);
        this->bytes.insert(this->bytes.end(), byte_tmp.begin(), byte_tmp.end());
    }
}

void ByteArrayOutputStream::write(char* b, int offset, int len)
{
	//int length = sizeof(b);
	int end = offset + len;
	/*if (end > length || offset < 0) {
		std::cout << "offset error" << std::endl;
		abort();
	}*/
	for (int i=offset; i < end; i++) {
		std::vector<std::uint8_t> byte_tmp = ToByte(b[len - i - 1]);
		this->bytes.insert(this->bytes.end(), byte_tmp.begin(), byte_tmp.end());
	}
}

void ByteArrayOutputStream::write2file()
{
	ofstream outfile;
	outfile.open(filepath, ios::app|ios::out|ios::binary);
	if (!outfile)
	{
		cout << "the file can't open" << endl;
		abort();
	}else
	{
		outfile << colnum << endl;
		for (auto d : bytesnum)
			outfile << d;
		//cout << this->bytes.size() << endl;
		for (std::uint8_t bt : this->bytes) {
			outfile <<  bt;
		}
		//cout << outfile. << endl;
		vector <std::uint8_t>().swap(this->bytes);
		//cout << this->bytes.size() << endl;
		outfile.close();
	}
}

std::vector<std::uint8_t> ByteArrayOutputStream::getBytes()
{
	return bytes;
}
