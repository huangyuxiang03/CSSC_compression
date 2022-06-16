#pragma once
#include "ByteArrayOutputStream.h"


template <typename T>
std::vector<std::uint8_t> ToByte(T input)
{
	std::uint8_t* bytePointer = reinterpret_cast<std::uint8_t*>(&input); 
	return std::vector<std::uint8_t>(bytePointer, bytePointer + sizeof(T));
}
template <typename T>
std::vector<std::uint8_t>& operator>>(std::vector<std::uint8_t>& in, T& out)
{
	if (in.size() >= sizeof(T)) {
		out = *reinterpret_cast<T*>(in.data());
		in.erase(in.begin(), in.begin() + sizeof(T));
		char* pp = (char*)&out;
	}
	else {
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

void ByteArrayOutputStream::write(char b)
{
	std::vector<std::uint8_t> bytes_tmp = ToByte(b);
	this->bytes.insert(this->bytes.end(), bytes_tmp.begin(), bytes_tmp.end());
}

void ByteArrayOutputStream::write(std::uint8_t b)
{
	this->bytes.push_back(b);
}

void ByteArrayOutputStream::writeBytes(char b[]){
	int len = sizeof(b);
	for (int i=0; i < len;i++) {
		std::vector<std::uint8_t> byte_tmp = ToByte(b[len - i - 1]);
        this->bytes.insert(this->bytes.end(), byte_tmp.begin(), byte_tmp.end());
		vector <std::uint8_t>().swap(byte_tmp);
    }
	//delete[] b;
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
		vector <std::uint8_t>().swap(byte_tmp);
	}
	//delete[] b;
}
void ByteArrayOutputStream::write(vector<std::uint8_t> b, int offset, int len)
{
	int end = offset + len;
	/*if (end > length || offset < 0) {
		std::cout << "offset error" << std::endl;
		abort();
	}*/
	//for (int i = offset; i < end; i++) {
	//	std::vector<std::uint8_t> byte_tmp = ToByte(b[len - i - 1]);
	this->bytes.insert(this->bytes.end(), b.begin(), b.end());
	vector <std::uint8_t>().swap(b);
	//}
}
void ByteArrayOutputStream::write(std::uint8_t* b, int offset, int len)
{
	int end = offset + len;
	for (int i = offset; i < end; i++) {
		this->bytes.push_back(b[i]);
	}
	//delete[] b;
}
//void ByteArrayOutputStream::compress() {
//	//int* olen;
//	int ilen = this->bytes.size();
//	std::uint8_t* idata = new std::uint8_t[ilen];
//	for (int i = 0; i < ilen;i++) {
//		 idata[i] = this->bytes[i];
//	}
//	//std::uint8_t* odata;
//	GZIP gzip;
//	this->compressed_bytes = new std::uint8_t[ilen];
//	gzip.data_compress(idata, ilen, this->compressed_bytes, this->olen);
//
//
//}
void ByteArrayOutputStream::write2file()
{
	ofstream outfile;
	outfile.open(filepath, ios::app | ios::out|ios::binary);
	if (!outfile){
		cout << "the file can't open" << endl;
		abort();
	}else
	{

		int size = this->bytes.size();
		char* buffer = new char[size];
		for (int i = 0; i < size; i++) {
			buffer[i] = this->bytes[i];
		}
		const char* const src = buffer;
		char* dst = new char[size];
		/*int srcSize = length;*/
		int dstlength = LZ4_compress_default(src, dst, size, size);
		//outfile << dst;
		cout << dstlength << endl;
		for (int i = 0; i < dstlength; i++) {
			outfile << dst[i];
		}
		//for (std::uint8_t bt : this->bytes) {
		//	outfile <<  bt;
		//}
		//outfile << "\n";

		vector <std::uint8_t>().swap(this->bytes);

		outfile.close();
	}
}

void ByteArrayOutputStream::readFromFile()
{
	ifstream infile;
	infile.open(filepath, ios::in | ios::binary);
	if (!infile)
	{
		cout << "the file can't open" << endl;
		abort();
	}
	else
	{
		infile.seekg(0, std::ios::end);
		int length = infile.tellg();
		infile.seekg(0, std::ios::beg);
		char* buffer = new char[length];    
		infile.read(buffer, length);
		int i = 0;
		std::vector<std::uint8_t> bytes_col_n;
		for (i = length - 4; i < length; i++) {
			bytes_col_n.push_back((std::uint8_t)buffer[i]);
		}
		bytes_col_n >> col_n;
		cout << "decode col num:" << col_n << endl;
		col_pos = new int[col_n];
		int col_start = length - 4 * (1+ col_n);
		i = col_start;
		for (int col_i_i = 0; col_i_i < col_n; col_i_i++) {
			std::vector<std::uint8_t> bytes_col_pos;
			for (; i < 4 * (col_i_i + 1)+ col_start; i++) {
				bytes_col_pos.push_back((std::uint8_t)buffer[i]);
			}
			bytes_col_pos >> col_pos[col_i_i];
			//cout << "col_pos[col_i_i] : " << col_pos[col_i_i] <<endl;

		}
		for (i=1; i < col_start; i++) {
			this->bytes.push_back((std::uint8_t)buffer[i]);
		}
		//col_pos = new int[100];
		//int col_i_i = 0;
		//for (int i = 0; i < length; i++) {
		//	//cout << buffer[i] << endl;
		//	if (buffer[i] == '\n') {	
		//		col_pos[col_n] = col_i_i;
		//		col_i_i = 0;
		//		col_n++;
		//		continue;
		//	}
		//	else {
		//		col_i_i++;
		//		this->bytes.push_back((std::uint8_t)buffer[i]);
		//	}
		//}
		cout << this->bytes.size() << endl;
		infile.close();
	}
}

void ByteArrayOutputStream::writeDatatype(char datatype)
{
	ofstream outfile;
	outfile.open(filepath, ios::out | ios::binary);
	if (!outfile)
	{
		cout << "the file can't open" << endl;
		abort();
	}
	else
	{
		outfile << (std::uint8_t) datatype;
		vector <std::uint8_t>().swap(this->bytes);
		outfile.close();
	}
}

std::vector<std::uint8_t> ByteArrayOutputStream::getInt()
{
	std::vector<std::uint8_t> getbytes;
	int getbytesnum = 4;
	getbytes.insert(getbytes.begin(), bytes.begin(), bytes.begin() + getbytesnum);
	bytes.erase(bytes.begin(), bytes.begin() + getbytesnum);
	return getbytes;
}

std::vector<std::uint8_t> ByteArrayOutputStream::getBytes()
{
	return bytes;
}

std::vector<std::uint8_t> ByteArrayOutputStream::getColBytes()
{
   std::vector<std::uint8_t> getbytes;
   getbytes.insert(getbytes.begin(), bytes.begin(), bytes.begin() + col_pos[col_index]);
   bytes.erase(bytes.begin(), bytes.begin() + col_pos[col_index]);
   col_index++;
   //col_n--;
   return getbytes;
}

// get bit_vector compressed part
std::vector<std::uint8_t> ByteArrayOutputStream::getBytesLength(int length)
{
	std::vector<std::uint8_t> getbytes;
	int getbytesnum = length / 8 + 1;
	getbytes.insert(getbytes.begin(), bytes.begin(), bytes.begin() + getbytesnum);
	bytes.erase(bytes.begin(), bytes.begin() + getbytesnum);
	return getbytes;
}
bool ByteArrayOutputStream::hasNextCol()
{
	if (col_n > col_index) return true;
	return false;
}

void ByteArrayOutputStream::writeRowCol(int col_nf, int* col_posf)
{
	ofstream outfile;
	outfile.open(filepath, ios::app | ios::out | ios::binary);
	if (!outfile)
	{
		cout << "the file can't open" << endl;
		abort();
	}
	else
	{

		for (int i = 1; i < col_nf + 1; i++) {
			std::vector<std::uint8_t> bytes_col_pos = ToByte(col_posf[i]);
			//cout << "col_posf[i] :" << col_posf[i] <<endl;
			for (std::uint8_t bt : bytes_col_pos) outfile << bt;
		}
		std::vector<std::uint8_t> bytes_col_n = ToByte(col_nf);
		for (std::uint8_t bt : bytes_col_n) {
           outfile << bt;
		} 
		outfile.close();
	}
}

void ByteArrayOutputStream::reset()
{
	vector <std::uint8_t>().swap(this->bytes);
	//this->bytes.clear();
}


