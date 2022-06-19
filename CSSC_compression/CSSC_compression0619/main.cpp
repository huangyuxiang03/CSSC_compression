#pragma once
#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "ByteArrayOutputStream.h"
#include "LongDeltaEncoder.h"
#include "IntDeltaEncoder.h"
#include "LongDeltaDecoder.h"
#include "FloatDeltaDecoder.h"
#include "FloatDeltaEncoder.h"
#include "RleEncoder.h"
#include "IntRleEncoder.h"
#include "FloatRleEncoder.h"
#include "BitVectorEncoder.h"
#include "BitVectorDecoder.h"
#include "IndexEncoder.h"
#include "IndexDecoder.h"
#include "IntRleDecoder.h"
//#include "FragmentEncoder.h"
#include "FloatRleDecoder.h"

#include "GZIP.h"

using namespace std;

int char2hex(char c) {
	int r=0;
	if (c >= '0' && c <= '9')
		r = c - 48;
	else if (c >= 'A' && c <= 'F')
		r = c - 55;
	return r;
}
ll char16toll(char* num) {
	return char2hex(num[0]) * 4096 + char2hex(num[1]) * 256 + char2hex(num[2]) * 16 + char2hex(num[3]);
}
int char16toint(char* num) {
	return char2hex(num[0]) * 4096 + char2hex(num[1]) * 256 + char2hex(num[2]) * 16 + char2hex(num[3]);
}
int char16toint4byte(char* num) {
	return char2hex(num[0]) * 4096 + char2hex(num[1]) * 256 + char2hex(num[2]) * 16 + char2hex(num[3]);
}
int char16toint3byte(char* num) {
	return char2hex(num[0]) * 256 + char2hex(num[1]) * 16 + char2hex(num[2]);
}
void int3bytetochar16(int num, char* ch) {
	int* ich = new int[3];
	ich[2] = num & 15;
	num >>= 4;
	ich[1] = num & 15;
	num >>= 4;
	ich[0] = num & 15;
	for (int i = 0; i < 3; i++) {
		if (ich[i] >= 10) ch[i] = ich[i] + 55;
		else if(ich[i] < 10) ch[i] = ich[i] + 48;
	}
	delete[] ich;
}
int char16toint2byte(char* num) {
	return char2hex(num[0]) * 16 + char2hex(num[1]);
}
float chartofloat(char* num) {
	return atof(num);
}
float chartoint(char* num) {
	return atoi(num);
}

//justify the number is int or float, if it is int, return 0;else return 1;
int justify_file(string filename) {
	int try_len = 10;
	char* buffer = new char[try_len];
	ifstream inFile;
	inFile.open(filename, ios::in | ios::binary);
	inFile.read(buffer, try_len);
	int jresult=0;
	for (int i = 0; i < try_len; i++) {
		if (buffer[i] == '.') {
			jresult = 1;
			break;
		}
	}
	return jresult;
}
//justify the number is ll or float, if it is ll, return 0;else return 1;
int justify_file_decode(string filename) {
	int try_len = 1;
	char* buffer = new char[try_len];
	ifstream inFile;
	inFile.open(filename, ios::in | ios::binary);
	inFile.read(buffer, try_len);
	int jresult = 2;
	if (buffer[0] == 'l') {
		jresult = 0;
	}
	else if (buffer[0] == 'f') {
		jresult = 1;
	}
	return jresult;
}

int** read_csvint7(string filename, char sep, int& row, int& col)
{
	ifstream inFile;
	inFile.open(filename, ios::in | ios::binary);
	int** strArray;
	//std::cout << filename << endl;
	inFile.seekg(0, std::ios::end);
	int length = inFile.tellg();
	cout << "read data: " << length << endl;
	inFile.seekg(0, std::ios::beg);
	char* buffer = new char[length + 1];
	inFile.read(buffer, length);
	if (buffer[length - 1] != '\n') buffer[length] = '\n';
	else length--;

	int i = 0;
	col = 7;
	row = 19000000;
	strArray = new int* [col];
	for (int j = 0; j < col; j++) {
		strArray[j] = new int[row];
	}

	//cout << "here" << endl;
	i = 0;
	int num_j = 0, row_n = 0, col_n = 0;
	char* num = new char[5];
	int num_some_row = 0;
	while (i != length + 1) {
		if (buffer[i] != '\n' && buffer[i] != '\r' && buffer[i] != sep) {
			num[num_j] = buffer[i];
			num_j++;
			num_some_row++;
			if (num_some_row == 2 || num_some_row == 4 ) {
				strArray[col_n][row_n] = char16toint2byte(num);
				delete[] num;
				num = new char[5];
				num_j = 0;
				col_n++;
			}
			else if (num_some_row == 8 ) {
				strArray[col_n][row_n] = char16toint4byte(num);
				delete[] num;
				num = new char[5];
				num_j = 0;
				col_n++;
			}
			else if (num_some_row == 11 ||
				num_some_row == 14 || num_some_row == 17 || num_some_row == 20) {
				strArray[col_n][row_n] = char16toint3byte(num);
				delete[] num;
				num = new char[5];
				num_j = 0;
				col_n++;
			}
		}else if (buffer[i] == '\n') {
			num_some_row = 0;
			row_n++;
			if (row_n == 180000) break;
			col_n = 0;
		}

		i++;
	}
	row = row_n;
	delete[] buffer;
	cout << "finish reading " << endl;
	return strArray;

}
float** read_csvf(string filename, char sep, int& row, int& col)//, float** miu_i)
{
	ifstream inFile;
	inFile.open(filename, ios::in | ios::binary);
	
	cout << "read data: " << endl;
	inFile.seekg(0, std::ios::end);
	int length = inFile.tellg();
	inFile.seekg(0, std::ios::beg);
	char* buffer = new char[length + 1];
	inFile.read(buffer, length);
	if (buffer[length - 1] != '\n') buffer[length] = '\n';
	else length--;
	cout << length << endl;

	int i = 0;
	// find \n
	while (i != length+1) {
		if (buffer[i] == sep)
			col++;
		if (buffer[i] == '\n') {
			col++;
			break;
		}
		i++;
	}
	i++;
	row = 600000; //row 可以固定
	float** strArray;
	strArray = new float * [col];
	//miu_i = new float* [col]; // 前i个数的均值
	//float* sum = new float[col];
	for (int j = 0; j < col; j++) {
		strArray[j] = new float[row];
		//miu_i[j] = new float[row];
		//sum[j] = 0;
	}

	i = 0;
	int num_j = 0, row_n = 0, col_n = 0;
	char* num = new char[10];
	while (i != length + 1) {
		if (buffer[i] != '\n' && buffer[i] != sep) {
			//num[num_j] = buffer[i];
			num_j++;
		}
		else if (buffer[i] == sep) {
			delete[] num;
			num = new char[num_j+1];
			for (int k = 0; k < num_j; k++) {
				num[k] = buffer[i - num_j + k];
			}
			strArray[col_n][row_n] = chartofloat(num);
			//sum[col_n] += strArray[col_n][row_n];
			//miu_i[col_n][row_n] = sum[col_n] / (row_n + 1);
			num_j = 0;
			col_n++;
		}
		else if (buffer[i] == '\n') {
			delete[] num;
			num = new char[num_j+1];
			for (int k = 0; k < num_j; k++) {
				num[k] = buffer[i - num_j + k];
			}
			strArray[col_n][row_n] = chartofloat(num);
			//sum[col_n] += strArray[col_n][row_n];
			//miu_i[col_n][row_n] = sum[col_n] / (row_n + 1);

			num_j = 0;
			row_n++;
			if (row_n == 51000) break;
			col_n = 0;
		}
		i++;
	}
	delete[] num;
	row = row_n;
	delete[] buffer;
	cout << "finish reading " << endl;
	return strArray;
}

void write_csvint7(string filename,int row, vector<int>& strArray0, vector<int>& strArray1, string seq, int col)
{
	ofstream outFile(filename);

	for (int i = 0; i < row; i++) {
		int j0 = 0;
		int j1 = 0;
		outFile << setiosflags(ios::uppercase) << setfill('0') << setw(2) << std::hex << strArray0[j0 * row + i];
		j0++;
		outFile << setiosflags(ios::uppercase) << setfill('0') << setw(2) << std::hex << strArray0[j0 * row + i];
		outFile << seq;
		j0++;
		outFile << setiosflags(ios::uppercase) << setfill('0') << setw(4) << std::hex << strArray0[j0 * row + i];
		outFile << seq;
		j0++;
		outFile << setiosflags(ios::uppercase) << setfill('0') << setw(3) << std::hex << strArray1[j1 * row + i];
		j1++;
		char* int3byte = new char[3];
		int3bytetochar16(strArray1[j1 * row + i], int3byte);
		outFile << int3byte[0];
		outFile << seq;
		outFile << int3byte[1];
		outFile << int3byte[2];
		j1++;
		int3bytetochar16(strArray1[j1 * row + i], int3byte);
		outFile << int3byte[0];
		outFile << int3byte[1];
		outFile << seq;
		outFile << int3byte[2];
		j1++;
		int3bytetochar16(strArray0[j0 * row + i], int3byte);
		outFile << int3byte[0];
		outFile << int3byte[1];
		outFile << int3byte[2];
		outFile << "\n";
		delete[] int3byte;
	}
	std::cout << "finish writing " << endl;
}
double round_double(double number, int loc)
{
	unsigned long long a;
	memcpy(&a, &number, sizeof(long long));
	if (a == 9223372036854775808)
		return number;
	

	switch (loc)
	{
	case 1:
		if (number > 0)
			return double(int((number + 0.05) * 10)) / 10;
		else
			return double(int((number - 0.05) * 10)) / 10;
	case 2:
		if (number > 0)
			return double(int((number + 0.005) * 100)) / 100;
		else
			return double(int((number - 0.005) * 100)) / 100;
	case 3:
		if (number > 0)
			return double(int((number + 0.0005) * 1000)) / 1000;
		else
			return double(int((number - 0.0005) * 1000)) / 1000;
	case 4:
		if (number > 0)
			return double(int((number + 0.00005) * 10000)) / 10000;
		else
			return double(int((number - 0.00005) * 10000)) / 10000;
	case 5:
		if (number > 0)
			return double(int((number + 0.000005) * 100000)) / 100000;
		else
			return double(int((number - 0.000005) * 100000)) / 100000;
	default:
		break;
	}
}
void write_csvf(string filename, vector<float>& strArray, string seq, int col)
{
	ofstream outFile(filename);
	//outFile.open(filename, ios::out );
	int length = strArray.size();
	int row = length / col;

	for (int i = 0; i < row; i++) {
		int j = 0;
		outFile.setf(ios::fixed, ios::floatfield);
		outFile << setprecision(3) << round_double(strArray[j * row + i], 3);
		j++;
		for (; j < col; j++) {
			outFile << seq;
			//outFile.setf(ios::fixed, ios::floatfield);
			outFile << setprecision(5) << round_double(strArray[j * row + i], 5);
		}
		outFile << "\r";
		outFile << "\n";
	}
	std::cout << "finish writing " << endl;
	//outFile.close();
}

int DATA_DECOMPRESSED_POS = 0;

int main(int argc, char* argv[]) {

	std::string testin;
	for (int i = 48; i <=156; i++) {
		int* idx_int = &i;
		char* idx =  (char*)idx_int;
		testin += idx[0];
	}

	std::string compressed_data = gzip::compress(testin.data(), testin.size());
	std::string uncompressed_data = gzip::decompress(compressed_data.data(), compressed_data.size());

	return 0;





	time_t start, end;
	double cost;
	time(&start);

	if (argc != 4) return 0;
	if (argv[1][0] == 'c') {
		//justify the number is ll or float
		int jresult = justify_file(argv[2]);
		//cout << jresult << endl;
		if (jresult==0) {
			/*std::cout << argv[2] << endl;*/
			
			int width = 0, length = 0;
			int** strArrayll =  read_csvint7(argv[2], ',', length, width);
			int* col_pos= new int[width+4]; // the position of per column data
			int col_n=0; //the number of remaining column of the ByteArrayOutputStream
			col_pos[0] = 0;
			std::cout << length << endl;
			std::cout << "width: " << width << endl;
			ByteArrayOutputStream out(argv[3]);
			out.writeDatatype('l');
			for (int i = 0; i < width; i++) {
				if (i == 10) {
					IndexEncoder encoder(length, strArrayll[i][0]);
					for (int j = 1; j < length; j++) {
						if (j % 18000000 == 0) {
							cout << "col:" << i << endl;
							cout << "row:" << j << endl;
						}
						encoder.encode(strArrayll[i][j], out);
					}
					encoder.flush(out);
					col_n++;
					col_pos[col_n] = encoder.getBit_vector1_num_count();
					out.write2file();
				}
				else if(i>=30&&i<=5){
					BitVectorEncoder encoder(length,1000);
					ByteArrayOutputStream out1(argv[3]);
					ByteArrayOutputStream out2(argv[3]);
					ByteArrayOutputStream out3(argv[3]);
					for (int j = 0; j < length; j++) {
						if (j % 18000000 == 0) {
							cout << "col:" << i << endl;
							cout << "row:" << j << endl;
						}
						encoder.encode(strArrayll[i][j],j, out1,out2);
					}
					
					encoder.flush(out1,out2);
					encoder.encode_bitvector(out3);
					out3.write2file();

					col_n++;
					out1.write2filelz4();
					col_pos[col_n] = out1.getCompressedBytesSize();
					//col_pos[col_n] = out1.getBytes().size();
     //               out1.write2file();

					col_n++;
					//col_pos[col_n] = out2.getBytes().size();
					//out2.write2file();
					out2.write2filelz4();
					col_pos[col_n] = out2.getCompressedBytesSize();
				}
				////else if(i==6) {
				////	IntDeltaEncoder encoder;
				////	for (int j = 0; j < length; j++) {
				////		if (j % 18000000 == 0) {
				////			cout << "col:" << i << endl;
				////			cout << "row:" << j << endl;
				////		}
				////		out.write(strArrayll[i][j]);
				////		//encoder.encode(strArrayll[i][j], out);
				////	}
				////	col_n++;
				////	//encoder.flush(out);
				////	//cout << out.getBytes().size() << endl;
				////	out.write2filelz4();
				////	col_pos[col_n] = out.getCompressedBytesSize();

				//}
				else {
					IntRleEncoder encoder;
					for (int j = 0; j < length; j++) {
						if (j %18000000==0) {
							cout << "col:"<<i << endl;
							cout << "row:" << j << endl;
						} 
						encoder.encode(strArrayll[i][j], out);
					}
					col_n++;
					encoder.flush(out);

					//col_pos[col_n] = out.getBytes().size();
					//out.write2file();
					
					out.write2filelz4();
					col_pos[col_n] = out.getCompressedBytesSize();
					
				}
				cout << "col_pos[" << col_n << "] : " << col_pos[col_n] << endl;
			}
			cout << "finish encoding" << endl;
			out.writeRowCol(col_n, col_pos);
			cout << "finish writing" << endl;
		}
		else if (jresult==1) {
			//int fi[] = {2112,5215,6963,9178,12435,14889,17973,22021,23504,23598,24779,26673,26848,27991,29773,29998,30998,31114,34088,36498,37628,38698,39598,39748,40853,42328,43283,45968,47782,48748};
			//int finum = 0;
			//std::cout << argv[2] << endl;
			ByteArrayOutputStream out(argv[3]);
			//float** miu_i;
			int width = 0, length = 0;
			float** strArrayll = read_csvf(argv[2], ' ', length, width);// , miu_i);
			int* col_pos = new int[width + 1]; // the position of per column data
			int col_n = 0; //the number of remaining column of the ByteArrayOutputStream
			col_pos[0] = 0;
			std::cout << length << endl;
			std::cout << width << endl;

			out.writeDatatype('f');
			int count = 0;
			for (int i = 0; i < width; i++) {
				//float miu = 0.0f;
				FloatRleEncoder* encoder = new FloatRleEncoder();
				//FloatDeltaEncoder* encoder = new FloatDeltaEncoder();
				//FragmentEncoder* encoder = new FragmentEncoder(miu,length);
				for (int j = 0; j < length; j++) {
					if (j% 510000==0) {
						cout << "col:" << i << endl;
						cout << "row:" << j << endl;
					}

					//int a = strArrayll[i][j] * 100000;
					//out.write(a);
					encoder->encode(strArrayll[i][j], out);
					
					//encoder->encode(strArrayll[i][j],j, out);
				}
				col_n++;
				encoder->flush(out);

				//encoder->encode_bitvector(out);

				//col_pos[col_n] = out.getBytes().size();
				//out.write2file();

				out.write2filelz4();
				col_pos[col_n] = out.getCompressedBytesSize();
				
				cout << "col_pos[" << col_n << "] : " << col_pos[col_n] << endl;
				time(&end);
				cost = difftime(end, start);
				std::cout << "time cost: " << cost << endl;
			}
			cout << "finish encode" << endl;
			out.writeRowCol(col_n, col_pos);
			cout << "finish writing" << endl;
		}
	}
	else if (argv[1][0] == 'd') {
		int jresult = justify_file_decode(argv[2]);
		std::cout << jresult << endl;
		time_t start_d, end_d;
		double cost_d;
		time(&start_d);		
		if (jresult == 0) {
			ByteArrayOutputStream baos(argv[2]);
			baos.readFromFile();

			vector<int> llArray0;
			vector<int> llArray1;
			int col = 0;
			int row_tol = 0;
			while (baos.hasNextCol()) {
				col++;
				if(col==1) {
					IntRleDecoder decoder;
					ByteBuffer in(baos.getColBytesLZ4());
					int lengthb = in.Bytes().size();
					cout << "current bytes length: " << lengthb << endl;
					while (decoder.hasNext(in)) {
						int r = decoder.readInt(in);
						row_tol++;
						llArray0.push_back(r);
					}
					cout <<"row_tol: " << row_tol << endl;
				}
				//else if (col == 20) {
				//	IndexDecoder decoder(row_tol, 0);
				//	ByteBuffer in_bit_vector0_count(baos.getInt());
				//	int bit_vector0_count = in_bit_vector0_count.readInt();
				//	ByteBuffer in3(baos.getBytesLength(bit_vector0_count));
				//	decoder.setBit_vector0_count(bit_vector0_count);
				//	decoder.decode_bitvector(in3);
				//	
				//	ByteBuffer in(baos.getColBytes());
				//	int lengthb = in.Bytes().size();
				//	cout << "current bytes length: " << lengthb << endl;
				//	decoder.readInt(llArray0, in);
				//}
				//else if (col >= 40 && col <= 6) {
				//	//cout << row_tol << endl;
				//	BitVectorDecoder decoder(row_tol,1000);
				//	ByteBuffer in3(baos.getBytesLength(row_tol));
				//	decoder.decode_bitvector(in3);
				//	ByteBuffer in1(baos.getColBytes());
				//	int lengthb = in1.Bytes().size();
				//	cout << "in1 lengthb: " << lengthb << endl;
				//	ByteBuffer in2(baos.getColBytes());
				//	lengthb = in2.Bytes().size();
				//	cout << "in2 lengthb: " << lengthb << endl;
				//	int rowj = 0;
				//	while (decoder.hasNext(in1,in2)&&rowj<row_tol) {
				//		int r = decoder.readInt(rowj, in1, in2);
				//		rowj++;
				//		llArray1.push_back(r);
				//	}
				//}
				else if (col >= 4 && col <= 6) {
					IntRleDecoder decoder;
					ByteBuffer in(baos.getColBytesLZ4());
					int lengthb = in.Bytes().size();
					cout << "current bytes length: " << lengthb << endl;
					while (decoder.hasNext(in)) {
						int r = decoder.readInt(in);
						llArray1.push_back(r);
					}
				}
				else {
					IntRleDecoder decoder;
					ByteBuffer in(baos.getColBytesLZ4());
					int lengthb = in.Bytes().size();
					cout << "current bytes length: " << lengthb << endl;
					while (decoder.hasNext(in)) {
						int r = decoder.readInt(in);
						llArray0.push_back(r);
					}
				}
				//std::cout << llArray.size() << endl;
			}
			write_csvint7(argv[3], row_tol, llArray0, llArray1,",",col);
		}
		else if (jresult == 1) {
			ByteArrayOutputStream baos(argv[2]);
			FloatRleDecoder decoder;
			baos.readFromFile();
			vector<float> fArray;
			int col = 0;

			while (baos.hasNextCol()) {
				col++;
				cout << "current column : " << col << endl;
				ByteBuffer in(baos.getColBytesLZ4());
				int lengthb = in.Bytes().size();
				cout << "length of decode bytes : "<< lengthb << endl;

				int count = 0;
				while (decoder.hasNext(in)) {
					float r = decoder.readFloat(in);
					fArray.push_back(r);
				}
				std::cout << fArray.size() << endl;
			}
			write_csvf(argv[3], fArray, " ", col);
		}
	}
	time(&end);
	cost = difftime(end, start);
	std::cout <<"time cost: " << cost << endl;
	return 0;
}
