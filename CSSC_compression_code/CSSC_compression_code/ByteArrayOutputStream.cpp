#pragma once
#include "ByteArrayOutputStream.h"
// 基础类型到容器转换
template <typename T>
std::vector<std::uint8_t> ToByte(T input)
{
	std::uint8_t* bytePointer = reinterpret_cast<std::uint8_t*>(&input);
	return std::vector<std::uint8_t>(bytePointer, bytePointer + sizeof(T));
}

// 容器到基础类型转换
template <typename T>
std::vector<std::uint8_t>& operator>>(std::vector<std::uint8_t>& in, T& out)
{
	if (in.size() >= sizeof(T)) {
		out = *reinterpret_cast<T*>(in.data());
		in.erase(in.begin(), in.begin() + sizeof(T));
	}else {
		out = T{ 0 };
	}
	return in;
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
		std::vector<std::uint8_t> byte_tmp = ToByte(b[i]);
        this->bytes.insert(this->bytes.end(), byte_tmp.begin(), byte_tmp.end());
    }
}

void ByteArrayOutputStream::write(char b[], int offset, int len)
{
	int length = sizeof(b);
	int end = offset + len;
	if (end > length || offset < 0) {
		std::cout << "offset error" << std::endl;
		abort();
	}
	for (int i=offset; i < end; i++) {
		std::vector<std::uint8_t> byte_tmp = ToByte(b[i]);
		this->bytes.insert(this->bytes.end(), byte_tmp.begin(), byte_tmp.end());
	}
}

void ByteArrayOutputStream::write2file()
{
	ofstream outfile;
	outfile.open(filepath, ios::app);
	if (!outfile)
	{
		cout << "the file can't open" << endl;
		abort();
	}else
	{
		for(std::uint8_t bt:this->bytes)
			outfile << bt << endl;
		vector <std::uint8_t>().swap(this->bytes);
		outfile.close();
	}
}
