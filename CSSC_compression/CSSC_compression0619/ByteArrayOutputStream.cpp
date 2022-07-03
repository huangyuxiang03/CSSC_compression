#pragma once
#include "ByteArrayOutputStream.h"

/**
 * @brief convert input to byte array
 * 
 * @tparam T 
 * @param input 
 * @return std::vector<std::uint8_t> 
 */
template <typename T>
std::vector<std::uint8_t> ToByte(T input)
{
	std::uint8_t* bytePointer = reinterpret_cast<std::uint8_t*>(&input); 
	return std::vector<std::uint8_t>(bytePointer, bytePointer + sizeof(T));
}
/**
 * @brief read from vector to variable
 * 
 * @tparam T 
 * @param in 
 * @param out 
 * @return std::vector<std::uint8_t>& 
 */
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
/**
 * @brief write int to vector
 * 
 * @param b 
 */
void ByteArrayOutputStream::write(int b){
   std::vector<std::uint8_t> bytes_tmp = ToByte(b);
   this->bytes.insert(this->bytes.end(),bytes_tmp.begin(),bytes_tmp.end());

}
/**
 * @brief  write long long to vector
 * 
 * @param b 
 */
void ByteArrayOutputStream::write(long long b){
   std::vector<std::uint8_t> bytes_tmp = ToByte(b);
   this->bytes.insert(this->bytes.end(),bytes_tmp.begin(),bytes_tmp.end());
}
/**
 * @brief  write char to vector
 * 
 * @param b 
 */
void ByteArrayOutputStream::write(char b)
{
	std::vector<std::uint8_t> bytes_tmp = ToByte(b);
	this->bytes.insert(this->bytes.end(), bytes_tmp.begin(), bytes_tmp.end());
}
/**
 * @brief write uint8_t to vector
 * 
 * @param b 
 */
void ByteArrayOutputStream::write(std::uint8_t b)
{
	this->bytes.push_back(b);
}
/**
 * @brief  write char array to vector
 * 
 * @param b 
 */
void ByteArrayOutputStream::writeBytes(char b[]){
	int len = sizeof(b);
	for (int i=0; i < len;i++) {
		std::vector<std::uint8_t> byte_tmp = ToByte(b[len - i - 1]);
        this->bytes.insert(this->bytes.end(), byte_tmp.begin(), byte_tmp.end());
		vector <std::uint8_t>().swap(byte_tmp);
    }
	//delete[] b;
}
/**
 * @brief 
 * 
 * @param b 
 * @param offset 
 * @param len 
 */
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
/**
 * @brief 
 * 
 * @param b 
 * @param offset 
 * @param len 
 */
void ByteArrayOutputStream::write(vector<std::uint8_t> b, int offset, int len)
{
	int end = offset + len;
	this->bytes.insert(this->bytes.end(), b.begin(), b.end());
	vector <std::uint8_t>().swap(b);
	//}
}
/**
 * @brief 
 * 
 * @param b 
 * @param offset 
 * @param len 
 */
void ByteArrayOutputStream::write(std::uint8_t* b, int offset, int len)
{
	int end = offset + len;
	for (int i = offset; i < end; i++) {
		this->bytes.push_back(b[i]);
	}
	//delete[] b;
}
/**
 * @brief 
 * 
 */
void ByteArrayOutputStream::write2file()
{
	ofstream outfile;
	outfile.open(filepath, ios::app | ios::out|ios::binary);
	if (!outfile){
		cout << "the file can't open" << endl;
		abort();
	}else
	{
		for (std::uint8_t bt : this->bytes) {
			outfile <<  bt;
		}
		//outfile << "\n";

		vector <std::uint8_t>().swap(this->bytes);

		outfile.close();
		//delete[] dst;
		//delete[] buffer;

	}		
}
/**
 * @brief 
 * 
 */
void ByteArrayOutputStream::write2filegzip()
{
	ofstream outfile;
	outfile.open(filepath, ios::app | ios::out | ios::binary);
	if (!outfile) {
		cout << "the file can't open" << endl;
		abort();
	}
	else
	{
		int olen=0;
		int ilen = this->bytes.size();
		std::uint8_t* idata = new std::uint8_t[ilen];
		for (int i = 0; i < ilen;i++) {
			 idata[i] = this->bytes[i];
		}
		GZIP gzip;
		std::uint8_t* compressed_bytes = new std::uint8_t[ilen*2];
		olen = gzip.data_compress(idata, ilen, compressed_bytes, ilen*2);

		cout << "ilen: " << ilen << endl;
		cout << "olen: " << olen << endl;
		dstlength = olen;
		
		//ofstream outfile1;
		//outfile1.open(filepath_compresssize , ios::app | ios::out );
		//outfile1 << olen << ',';
		//outfile1.close();

		for (int i = 0; i < dstlength; i++) {
			outfile << compressed_bytes[i];
		}
		delete[] compressed_bytes;
		delete[] idata;

		vector <std::uint8_t>().swap(this->bytes);

		outfile.close();

		//delete[] dst;
	}
}
/**
 * @brief 
 * 
 */
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
			
		}
		for (i=1; i < col_start; i++) {
			this->bytes.push_back((std::uint8_t)buffer[i]);
		}

		cout << this->bytes.size() << endl;
		infile.close();
	}
}
/**
 * @brief 
 * 
 * @param datatype 
 */
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
/**
 * @brief 
 * 
 * @return std::vector<std::uint8_t> 
 */
std::vector<std::uint8_t> ByteArrayOutputStream::getInt()
{
	std::vector<std::uint8_t> getbytes;
	int getbytesnum = 4;
	getbytes.insert(getbytes.begin(), bytes.begin(), bytes.begin() + getbytesnum);
	bytes.erase(bytes.begin(), bytes.begin() + getbytesnum);
	return getbytes;
}
/**
 * @brief 
 * 
 * @return std::vector<std::uint8_t> 
 */
std::vector<std::uint8_t> ByteArrayOutputStream::getBytes()
{
	return bytes;
}
/**
 * @brief 
 * 
 * @return int 
 */
int ByteArrayOutputStream::getCompressedBytesSize()
{
	return dstlength;
}
/**
 * @brief 
 * 
 * @return std::vector<std::uint8_t> 
 */
std::vector<std::uint8_t> ByteArrayOutputStream::getColBytes()
{
   std::vector<std::uint8_t> getbytes;
   getbytes.insert(getbytes.begin(), bytes.begin(), bytes.begin() + col_pos[col_index]);
   bytes.erase(bytes.begin(), bytes.begin() + col_pos[col_index]);
   col_index++;
   return getbytes;

}
/**
 * @brief 
 * 
 * @return std::vector<std::uint8_t> 
 */
std::vector<std::uint8_t> ByteArrayOutputStream::getColBytesGZip()
{
	std::vector<std::uint8_t> getbytes;
	getbytes.insert(getbytes.begin(), bytes.begin(), bytes.begin() + col_pos[col_index]);
	bytes.erase(bytes.begin(), bytes.begin() + col_pos[col_index]);
	col_index++;

	int olen = 0;
	int ilen = getbytes.size();
	std::uint8_t* idata = new std::uint8_t[ilen];
	for (int i = 0; i < ilen; i++) {
		idata[i] = getbytes[i];
	}
	GZIP gzip;
	int dstsize = max(100000000, ilen * 100);
	uint8_t* decompressed_bytes = new uint8_t[dstsize];
	//std::string decompressed_bytes;
	olen = gzip.data_decompress(idata, ilen, decompressed_bytes, dstsize);
	cout << "ilen: " << ilen << endl;
	cout << "olen: " << olen << endl;
	int decompdstlength = olen;

	std::vector<std::uint8_t> newgetbytes(decompdstlength);
	for (int i = 0; i < decompdstlength; i++) {
		newgetbytes[i] = decompressed_bytes[i];
	}
	delete[] decompressed_bytes;
	delete[] idata;
	return newgetbytes;
}
/**
 * @brief get bit_vector compressed part
 * 
 * @param length 
 * @return std::vector<std::uint8_t> 
 */
std::vector<std::uint8_t> ByteArrayOutputStream::getBytesLength(int length)
{
	std::vector<std::uint8_t> getbytes;
	int getbytesnum = length / 8 + 1;
	getbytes.insert(getbytes.begin(), bytes.begin(), bytes.begin() + getbytesnum);
	bytes.erase(bytes.begin(), bytes.begin() + getbytesnum);
	
	return getbytes;

}
/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool ByteArrayOutputStream::hasNextCol()
{
	if (col_n > col_index) return true;
	return false;
}
/**
 * @brief 
 * 
 * @param col_nf 
 * @param col_posf 
 */
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
/**
 * @brief 
 * 
 */
void ByteArrayOutputStream::reset()
{
	vector <std::uint8_t>().swap(this->bytes);
	//this->bytes.clear();
}
/**
 * @brief 
 * 
 */
void ByteArrayOutputStream::addSizeBack() {
	int sz = bytes.size();
	std::uint8_t* u = (std::uint8_t*)&sz;
	for(int i = 0; i < 4; i++)
		bytes.push_back(*(u+i));
}
/**
 * @brief 
 * 
 * @param b 
 */
void ByteArrayOutputStream::concatenate(ByteArrayOutputStream& b) {
	bytes.insert(bytes.end(), b.bytes.begin(), b.bytes.end());
}


