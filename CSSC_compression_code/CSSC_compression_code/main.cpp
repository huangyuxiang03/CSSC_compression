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
//#include "IntFunctionEncoder.h"
#include "LongDeltaDecoder.h"
#include "FloatDeltaDecoder.h"
#include "FloatDeltaEncoder.h"
#include "RleEncoder.h"
#include "IntRleEncoder.h"

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

float chartofloat(char* num) {
	return atof(num);
}

float chartoint(char* num) {
	return atoi(num);
}

//justify the number is ll or float, if it is ll, return 0;else return 1;
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

int** read_csvint(string filename, char sep, int& row, int& col)
{
	ifstream inFile;
	inFile.open(filename, ios::in | ios::binary);
	int** strArray;
	cout << "read data: " << endl;
	inFile.seekg(0, std::ios::end);
	int length = inFile.tellg();
	inFile.seekg(0, std::ios::beg);
	char* buffer = new char[length + 1];
	inFile.read(buffer, length);
	if (buffer[length - 1] != '\n') buffer[length] = '\n';
	else length--;

	cout << length << endl;
	//int i = 0, col=0,row=0;
	int i = 0;
	// find \n
	while (i != length + 1) {
		if (buffer[i] == sep)
			col++;
		if (buffer[i] == '\n') {
			col++;
			break;
		}
		i++;
	}
	i++;

	row = (length + 1) / i;
	strArray = new int* [col];
	for (int j = 0; j < col; j++) {
		strArray[j] = new int[row];
	}

	//cout << "here" << endl;
	i = 0;
	int num_j = 0, row_n = 0, col_n = 0;
	char* num = new char[5];
	while (i != length + 1) {
		if (buffer[i] != '\n' && buffer[i]!='\r' && buffer[i] != sep) {
			num[num_j] = buffer[i];
			num_j++;
		}
		else if (buffer[i] == sep) {
			strArray[col_n][row_n] = char16toint(num);
			delete[] num;
			num = new char[5];
			num_j = 0;
			col_n++;
		}
		else if (buffer[i] == '\n') {
			strArray[col_n][row_n] = char16toint(num);
			delete[] num;
			num = new char[5];
			num_j = 0;
			row_n++;
			if (row_n == 18000) break;
			col_n = 0;
			
		}
		i++;
	}
	row = row_n;
	delete[] buffer;
	cout << "finish reading " << endl;
	return strArray;

}

int** read_csvint_vector(string filename, char sep, int& row, int& col)
{
	ifstream inFile;
	inFile.open(filename, ios::in | ios::binary);
	int** strArray;
	cout << "read data: " << endl;
	inFile.seekg(0, std::ios::end);
	int length = inFile.tellg();
	inFile.seekg(0, std::ios::beg);
	char* buffer = new char[length + 1];
	inFile.read(buffer, length);
	if (buffer[length - 1] != '\n') buffer[length] = '\n';
	else length--;
	cout << length << endl;
	//int i = 0, col=0,row=0;
	int i = 0;
	// find \n
	while (i != length + 1) {
		if (buffer[i] == sep) {
			col++;
			cout << col << endl;
		}

		if (buffer[i] == '\n') {
			col++;
			break;
		}
		i++;
	}

	i++;
	row = 20000000;// (length + 1) / i;
	strArray = new int* [col];
	for (int j = 0; j < col; j++) {
		strArray[j] = new int[row];
	}
	//cout << "here" << endl;
	i = 0;

	int num_j = 0, row_n = 0, col_n = 0;
	char* num = new char[5];
	while (i != length + 1) {
		if (buffer[i] != '\n' && buffer[i] != sep) {
			num[num_j] = buffer[i];
			num_j++;
		}
		else if (buffer[i] == sep) {
			strArray[col_n][row_n] = chartoint(num);
			delete[] num;
			num = new char[5];
			num_j = 0;
			col_n++;
		}
		else if (buffer[i] == '\n') {
			strArray[col_n][row_n] = chartoint(num);
			delete[] num;
			num = new char[5];
			num_j = 0;
			row_n++;
			//cout << row_n << endl;
			//if (row_n == 180000) break;
			col_n = 0;
		}
		i++;
	}
	row = row_n;
	delete[] buffer;
	cout << "finish reading " << endl;
	return strArray;

}

ll** read_csvll(string filename,char sep, int& row,int& col)
{
	ifstream inFile;
	inFile.open(filename, ios::in | ios::binary);
	ll** strArray;
	cout << "read data: " << endl;
	inFile.seekg(0, std::ios::end);
	int length = inFile.tellg();
	inFile.seekg(0, std::ios::beg);
	char* buffer = new char[length+1];
	inFile.read(buffer, length);
	if (buffer[length - 1] != '\n') buffer[length] = '\n';
	else length--;
	cout << length << endl;
	//int i = 0, col=0,row=0;
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
	row = (length + 1) / i;
	strArray = new ll * [col];
	for (int j = 0; j < col; j++) {
		strArray[j] = new ll[row];
	}

	i = 0;
	int num_j = 0,row_n=0,col_n=0;
	char* num = new char[4];
	while (i != length+1) {
		if (buffer[i] != '\n' && buffer[i] != sep) {
			num[num_j] = buffer[i];
			num_j++;
		}
		else if (buffer[i] == sep) {
			strArray[col_n][row_n] = char16toll(num);
			delete[] num;
			num = new char[4];
			num_j = 0;
			col_n++;
		}
		else if (buffer[i] == '\n') {
			strArray[col_n][row_n] = char16toll(num);
			delete[] num;
			num = new char[4];
			num_j = 0;
			row_n++;
			//if (row_n == 1000) break;
			col_n = 0;
		}
		i++;
	}
	row = row_n;
	delete[] buffer;
	cout << "finish reading " << endl;
	return strArray;

}

float** read_csvf(string filename, char sep, int& row, int& col)
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
	//int i = 0, col=0,row=0;
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
	row = 1000000; //row 可以固定
	float** strArray;
	strArray = new float * [col];
	for (int j = 0; j < col; j++) {
		strArray[j] = new float[row];
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
			num_j = 0;
			row_n++;
			//if (row_n == 10) break;
			col_n = 0;
		}
		i++;
		//if(i%1000000 == 0)
		//	cout << (double)i / length << endl;
	}
	delete[] num;
	row = row_n;
	delete[] buffer;
	cout << "finish reading " << endl;
	return strArray;
}
void write_csvint(string filename, vector<int>& strArray, string seq, int col)
{
	ofstream outFile(filename);
	//outFile.open(filename, ios::out );
	int length = strArray.size();
	int row = length / col;

	for (int i = 0; i < row; i++) {
		int j = 0;
		for (; j < col - 1; j++) {
			outFile << setiosflags(ios::uppercase) << setfill('0') << setw(4) << std::hex << strArray[j * row + i];
			outFile << seq;
		}
		outFile << setiosflags(ios::uppercase) << setfill('0') << setw(4) << std::hex << strArray[j * row + i];
		outFile << "\n";
	}
	std::cout << "finish writing " << endl;
	//outFile.close();
}

void write_csvll(string filename, vector<ll>& strArray, string seq, int col)
{
	ofstream outFile(filename);
	//outFile.open(filename, ios::out );
	int length = strArray.size();
	int row = length / col;
	
	for (int i = 0; i < row; i++) {
		int j = 0;
		for (; j < col - 1; j++) {
			outFile << setiosflags(ios::uppercase) << setfill('0') << setw(4) << std::hex << strArray[j * row + i];
			outFile << seq;
		}
		outFile << setiosflags(ios::uppercase) << setfill('0') << setw(4) << std::hex << strArray[j * row + i];
		outFile << "\n";
	}
	std::cout << "finish writing " << endl;
	//outFile.close();
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
		//cout << strArray[j * row + i];
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

int main(int argc, char* argv[]) {
	time_t start, end;
	double cost;
	time(&start);
	//ByteArrayOutputStream out("c:\\users\\xiaoj\\documents\\github\\cssc_compression\\cssc_compression_code\\debug\\well05191");
	//IntFunctionEncoder encoder;
	//int width = 0, length = 0;
	//int** strArrayll = read_csvint("c:\\users\\xiaoj\\documents\\github\\cssc_compression\\cssc_compression_code\\debug\\data_well_public.hxv", ',', length, width);
	//int* col_pos = new int[width + 1]; // the position of per column data
	//int col_n = 0; //the number of remaining column of the ByteArrayOutputStream
	//col_pos[0] = 0;
	//std::cout << length << endl;
	//std::cout << width << endl;
	//out.writeDatatype('l');
	//for (int i = 3; i < 4; i++) {
	//	for (int j = 0; j < length; j++) {
	//		if (j == 18000000) cout << j << endl;
	//		encoder.encode(strArrayll[i][j], out);
	//	}
	//	col_n++;
	//	encoder.flush(out);
	//	col_pos[col_n] = out.getBytes().size();
	//	out.write2file();
	//}
	//cout << "finish encoding" << endl;
	//out.writeRowCol(col_n, col_pos);
	//cout << "finish writing" << endl;


	if (argc != 4) return 0;
	if (argv[1][0] == 'c') {
		//justify the number is ll or float
		int jresult = justify_file(argv[2]);
		cout << jresult << endl;
		if (jresult==0) {
			//std::cout << argv[2] << endl;
			ByteArrayOutputStream out(argv[3]);
			IntRleEncoder encoder;
			//LongDeltaEncoder encoder;
			int width = 0, length = 0;
			int** strArrayll =  read_csvint(argv[2], ',', length, width);
			//ll** strArrayll = read_csvll(argv[2], ',', length, width);
			int* col_pos= new int[width+1]; // the position of per column data
			int col_n=0; //the number of remaining column of the ByteArrayOutputStream
			col_pos[0] = 0;
			std::cout << length << endl;
			std::cout << "width: " << width << endl;
			out.writeDatatype('l');
			for (int i = 0; i < width; i++) {
				for (int j = 0; j < length; j++) {
					if (j == 18000000) cout << j << endl;
					encoder.encode(strArrayll[i][j], out);
				}
				cout << endl;
				col_n++;
				encoder.flush(out);
				col_pos[col_n] =out.getBytes().size();
				out.write2file();
			}
			cout << "finish encoding" << endl;
			out.writeRowCol(col_n, col_pos);
			cout << "finish writing" << endl;
		}
		else if (jresult==1) {
			//std::cout << argv[2] << endl;
			ByteArrayOutputStream out(argv[3]);
			FloatDeltaEncoder encoder;
			int width = 0, length = 0;
			float** strArrayll = read_csvf(argv[2], ' ', length, width);
			int* col_pos = new int[width + 1]; // the position of per column data
			int col_n = 0; //the number of remaining column of the ByteArrayOutputStream
			col_pos[0] = 0;
			std::cout << length << endl;
			std::cout << width << endl;
			out.writeDatatype('f');
			for (int i = 0; i < width; i++) {
				for (int j = 0; j < length; j++) {
					//if (j% 10000==0) {
     //                   cout << "压缩至第" << j << "行" << endl;
					//	//break;
					//} 
					encoder.encode(strArrayll[i][j], out);
				}
				col_n++;
				encoder.flush(out);
				col_pos[col_n] = out.getBytes().size();
				cout << "col_pos[" << col_n << "] : " << col_pos[col_n] << endl;
				out.write2file();
			}
			cout << "finish encode" << endl;
			out.writeRowCol(col_n, col_pos);
			cout << "finish writing" << endl;
		}
	}
	else if (argv[1][0] == 'd') {
		int jresult = justify_file_decode(argv[2]);
		cout << jresult << endl;
		time_t start_d, end_d;
		double cost_d;
		time(&start_d);		
		if (jresult == 0) {
			ByteArrayOutputStream baos(argv[2]);
			IntDeltaDecoder decoder;
			baos.readFromFile();

			vector<int> llArray;
			int col = 0;
			
			while (baos.hasNextCol()) {
				col++;
				//	cout << "current column : " << col << endl;
				ByteBuffer in(baos.getColBytes());
				int lengthb = in.Bytes().size();
				cout << lengthb << endl;
				int count = 0;
				while (decoder.hasNext(in)) {
					int r = decoder.readInt(in);
					llArray.push_back(r);
					//if (count % 50000 ==0 ) {
					//	time(&end_d);
					//	cost_d = difftime(end_d, start_d);
					//	cout << count << endl;
					//	std::cout << "decode read time :" << cost_d << endl;
					//}
					//count++;
				}
				std::cout << llArray.size() << endl;
			}
			write_csvint(argv[3], llArray, ",",col);
		}
		else if (jresult == 1) {
			ByteArrayOutputStream baos(argv[2]);
			FloatDeltaDecoder decoder;
			baos.readFromFile();
			vector<float> fArray;
			int col = 0;

			while (baos.hasNextCol()) {
				col++;
				cout << "current column : " << col << endl;
				ByteBuffer in(baos.getColBytes());
				int lengthb = in.Bytes().size();
				cout << "length of decode bytes : "<< lengthb << endl;

				int count = 0;
				while (decoder.hasNext(in)) {
					float r = decoder.readFloat(in);
					fArray.push_back(r);
					if (count % 10000 == 0) {
						//time(&end_d);
						//cost_d = difftime(end_d, start_d);
						//time(&start_d);
						//std::cout << "decode read time :" << cost_d << endl;
						cout << count << endl;
					}
					count++;
				}
				//cout << col << endl;
				std::cout << fArray.size() << endl;
			}
			write_csvf(argv[3], fArray, " ", col);
		}
	}
	time(&end);
	cost = difftime(end, start);
	std::cout << cost << endl;
	return 0;
}
