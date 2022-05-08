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
#include "LongDeltaDecoder.h"
#include "FloatDeltaDecoder.h"
#include "FloatDeltaEncoder.h"
using namespace std;
vector<string> split(string str, string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str += pattern;
	int size = str.size();
	for (int i = 0; i < size; i++)
	{
		pos = str.find(pattern, i);
		if (pos < size)
		{
			std::string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}
vector<std::vector<string>> split2(string str, string pattern, string seq)
{
	std::string::size_type pos;
	std::vector<std::vector<string>> result;
	str += pattern;
	int size = str.size();
	for (int i = 0; i < size; i++)
	{
		pos = str.find(pattern, i);
		if (pos < size)
		{
			std::string s = str.substr(i, pos - i);
			std::vector<std::string> resline = split(s, seq);
			result.push_back(resline);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}

void stringSplit(const string& str, const char split, vector<string>& res)
{
	if (str == "")		return;
	string strs = str + split;
	size_t pos = strs.find(split);

	while (pos != strs.npos)
	{
		string temp = strs.substr(0, pos);
		//res.push_back(temp);
		strs = strs.substr(pos + 1, strs.size());
		pos = strs.find(split);
	}
}

void stringSplit2(const string& str, const char split, const char seq, vector<vector<string>>& res)
{
	if (str == "")		return;
	string strs = str + split;
	size_t pos = strs.find(split);

	while (pos != strs.npos)
	{
		vector<string> resVec;
		string temp = strs.substr(0, pos);
		stringSplit(temp, seq, resVec);
		//res.push_back(resVec);
		//cout << resVec[0] << endl;
		strs = strs.substr(pos + 1, strs.size());
		pos = strs.find(split);
	}
}
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
float chartofloat(char* num) {
	return atof(num);
}
ll** read_csvll(string filename,char sep, int subrow, int& row,int& col)
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
	buffer[length] = '\n';
	cout << length << endl;
	if (subrow != 0) {
		length = subrow;
	}
	//int i = 0, col=0,row=0;
	int i = 0;
	// find \n
	while (i != length) {
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
			num = new char[4];
			num_j = 0;
			col_n++;
		}
		else if (buffer[i] == '\n') {
			strArray[col_n][row_n] = char16toll(num);
			num = new char[4];
			num_j = 0;
			row_n++;
			col_n = 0;
		}
		i++;
	}
	
	delete[] buffer;
	cout << "finish reading " << endl;
	return strArray;

}
float** read_csvf(string filename, char sep, int subrow, int& row, int& col)
{
	ifstream inFile;
	inFile.open(filename, ios::in | ios::binary);
	float** strArray;
	cout << "read data: " << endl;
	inFile.seekg(0, std::ios::end);
	int length = inFile.tellg();
	inFile.seekg(0, std::ios::beg);
	char* buffer = new char[length + 1];
	inFile.read(buffer, length);
	buffer[length] = '\n';
	cout << length << endl;
	if (subrow != 0) {
		length = subrow;
	}
	//int i = 0, col=0,row=0;
	int i = 0;
	// find \n
	while (i != length) {
		if (buffer[i] == sep)
			col++;
		if (buffer[i] == '\n') {
			col++;
			break;
		}
		i++;
	}
	i++;
	row = 1000000; //row ¿ÉÒÔ¹Ì¶¨
	strArray = new float * [col];
	for (int j = 0; j < col; j++) {
		strArray[j] = new float[row];
	}

	i = 0;
	int num_j = 0, row_n = 0, col_n = 0;
	char* num = new char[10];
	while (i != length + 1) {
		if (buffer[i] != '\n' && buffer[i] != sep) {
			num[num_j] = buffer[i];
			num_j++;
		}
		else if (buffer[i] == sep) {
			//char* numt = new char[num_j];
			//for (int ni = 0; ni < num_j; ni++) numt[ni] = num[ni];
			strArray[col_n][row_n] = chartofloat(num);
			//cout << strArray[col_n][row_n] << endl;
			num = new char[10];
			num_j = 0;
			col_n++;
		}
		else if (buffer[i] == '\n') {
			//char* numt = new char[num_j];
			//for (int ni = 0; ni < num_j; ni++) numt[ni] = num[ni];
			strArray[col_n][row_n] = chartofloat(num);
			//cout.setf(ios::fixed, ios::floatfield);
			//cout << strArray[col_n][row_n] << endl;
			//if (row_n % 100==0) cout << row_n << endl;
			num = new char[10];
			num_j = 0;
			row_n++;
			col_n = 0;
		}
		i++;
	}
	row = row_n;
	delete[] buffer;
	cout << "finish reading " << endl;
	return strArray;

}

template <typename T>
vector<vector<T>> transpose(vector<vector<T>> strArray) {
	int length = strArray.size();
	cout << length << endl;
	vector<T> strArray0 = strArray[0];
	int width = strArray0.size();

	vector<vector<T>> resArray;
	for (int i = 0; i < width; i++) {
		vector<T> preArray;
		for (int j = 0; j < length; j++) {
			preArray.push_back(strArray[j][i]);
		}
		resArray.push_back(preArray);
	}
	return resArray;
}

template <typename T>
vector<T> flat(vector<vector<T>> strArray) {
	int length = strArray.size();
	cout << length << endl;
	vector<T> strArray0 = strArray[0];
	int width = strArray0.size();
	cout << width << endl;
	vector<T> resArray;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < length; j++) {
			resArray.push_back(strArray[j][i]);
		}
	}
	return resArray;
}

void write_csvll(string filename, vector<ll>& strArray, string seq, int col)
{
	ofstream outFile(filename);
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
}

void write_csvf(string filename, vector<float>& strArray, string seq, int col)
{
	ofstream outFile(filename);
	int length = strArray.size();
	int row = length / col;

	for (int i = 0; i < row; i++) {
		int j = 0;
		outFile.setf(ios::fixed, ios::floatfield);
		outFile << setprecision(3) << strArray[j * row + i];
		j++;
		for (; j < col; j++) {
			outFile << seq;
			outFile.setf(ios::fixed, ios::floatfield);
			outFile << setprecision(5) << strArray[j * row + i];
		}
		outFile << "\n";
	}
	std::cout << "finish writing " << endl;
}

int main(int argc, char* argv[]) {
	time_t start, end;
	double cost;
	time(&start);
	//int width = 0, length = 0;
	//float** strarrayll = read_csvf("c:\\users\\xiaoj\\documents\\github\\cssc_compression\\cssc_compression_code\\x64\\debug\\shore_public.dat", ' ', 0, length, width);

	//cout << argc << endl;
	if (argc != 4) return 0;

	std::cout << argv[1] << endl;
	if (argv[1][0] == 'c') {
		if (!strcmp(argv[2], "data_well_public.hxv")) {
			std::cout << argv[2] << endl;
			ByteArrayOutputStream out(argv[3]);
			LongDeltaEncoder encoder;
			int width = 0, length = 0;
			ll** strArrayll = read_csvll(argv[2], ',', 0, length, width);

			std::cout << length << endl;
			std::cout << width << endl;
			for (int i = 0; i < width; i++) {
				for (int j = 0; j < length; j++) {
					if (j % 1000000 == 0) cout << j << endl;
					encoder.encode(strArrayll[i][j], out);
				}
			}
			cout << "finish encode" << endl;
			encoder.flush(out);
			out.write2file();
		}
		else if (!strcmp(argv[2], "shore_public1.dat")) {
			std::cout << argv[2] << endl;
			ByteArrayOutputStream out(argv[3]);
			LongDeltaEncoder encoder;
			int width = 0, length = 0;
			float** strArrayll = read_csvf(argv[2], ' ', 0, length, width);

			std::cout << length << endl;
			std::cout << width << endl;
			for (int i = 0; i < width; i++) {
				for (int j = 0; j < length; j++) {
					if (j % 1000000 == 0) cout << j << endl;
					encoder.encode(strArrayll[i][j], out);
				}
			}
			cout << "finish encode" << endl;
			encoder.flush(out);
			out.write2file();

		}
	}
	else if (argv[1][0] == 'd') {
		if (!strcmp(argv[3], "data_well_public1.hxv")) {
			std::cout << argv[3] << endl;
			ByteArrayOutputStream out(argv[2]);
			LongDeltaDecoder decoder;
			out.readFromFile();
			ByteBuffer in(out.getBytes());
			int length = out.getBytes().size();
			vector<long long> llArray;
			while(decoder.hasNext(in)) {
			    ll r = decoder.readLong(in);
				llArray.push_back(r);
			}
			std::cout<< llArray.size() << endl;
			write_csvll(argv[3], llArray, ",",5);
		}
		else if (!strcmp(argv[3], "shore_public1.dat")) {
			std::cout << argv[3] << endl;
			ByteArrayOutputStream out(argv[2]);
			FloatDeltaDecoder decoder;
			out.readFromFile();
			ByteBuffer in(out.getBytes());
			int length = out.getBytes().size();
			vector<float> fArray;
			while (decoder.hasNext(in)) {
				float r = decoder.readFloat(in);
				fArray.push_back(r);
			}
			std::cout << fArray.size() << endl;
			write_csvf(argv[3], fArray, " ", 71);
		}
	}
	time(&end);
	cost = difftime(end, start);
	std::cout << cost << endl;
	return 0;
}

//vector<vector<float>> strArrayf;
//ByteArrayOutputStream out(argv[3]);
//
//read_csv(argv[2], strArrayf, ' ',50000);

//int length = strArrayf.size();
//std::cout << length << endl;
//vector<float> strArray0 = strArrayf[0];
//int width = strArray0.size();
//std::cout << width << endl;
//for (int i = 0; i < width; i++) {
//	FloatDeltaEncoder encoder;
//	for (int j = 0; j < length; j++) {
//		encoder.encode(strArrayf[j][i], out);
//	}
//	encoder.flush(out);
//	out.write2file();
//}

//string strBuffer(buffer);
//vector<vector<string>> strvv;
//stringSplit2(strBuffer, '\n', ',', strvv);
// cout << strvv[1][0] << endl;
//vector<vector<string>> str = split2(strBuffer, "\n", ",");
//cout << str[1][0] << endl;

//cout << inFile.is_open() << endl;
//while (getline(inFile, lineStr))
//{
//	if (i > row) break;
//	i++;
//	//cout << "iiiii" << endl;
//	stringstream ss(lineStr);
//	string str;
//	T str2long;
//	vector<T> lineArray;
//	while (getline(ss, str, seq))
//	{
//		stringstream strIn;
//		strIn << str;
//		T llNum;
//		strIn >> std::hex >> llNum;
//		//lineArray.push_back(llNum);
//	}
//	//strArray.push_back(lineArray);
//}

//return i;
//cout << "--------------------------------------------" << endl;
// cout << "print what we have saved in the vector: " << endl;
// for (auto s : strArray)
// {
//     for (auto x : s)
//     {
//         cout << x << " ";
//     }
//     cout << endl;
// }
//vector<vector<long long>> strArrayll;
//read_csv(argv[2], strArrayll, ',',180000);

//vector<vector<long long>> resArray = transpose(strArrayll);
//for (vector<long long> perArrayll : resArray) {
//	for (ll num : perArrayll) {
//		encoder.encode(num, out);
//	}
//}
//cout << resArray[0].size() << endl;
//vector<long long> resArray = flat(strArrayll);
//for (ll num : resArray) {
//	encoder.encode(num, out);
//}
//cout << resArray.size() << endl;

//int length = strArrayll.size();

//vector<ll> strArray0 = strArrayll[0];
//int width = strArray0.size();