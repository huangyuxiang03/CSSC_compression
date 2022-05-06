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

template <typename T>
void read_csv(string filename, vector<vector<T>>& strArray, char seq, int row)
{
	ifstream inFile(filename);
	string lineStr;
	cout << "read data: " << endl;
	int i = 0;
	if (row == 0) {
		row = 100000000;
	}
	while (getline(inFile, lineStr))
	{
		if (i > row) break;
		i++;
		//cout << lineStr << endl;
		stringstream ss(lineStr);
		string str;
		T str2long;
		vector<T> lineArray;
		while (getline(ss, str, seq))
		{
			stringstream strIn;
			strIn << str;
			T llNum;
			strIn >> std::hex >> llNum;
			lineArray.push_back(llNum);
		}
		strArray.push_back(lineArray);
	}
	cout << "finish reading " << endl;
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
		string lineStr;
		int j = 0;
		for (; j < col - 1; j++) {
			outFile << setiosflags(ios::uppercase) << setfill('0') << setw(4) << std::hex << strArray[j * row + i];
			outFile << seq;
		}
		outFile << setiosflags(ios::uppercase) << setfill('0') << setw(4) << std::hex << strArray[j * row + i];
		outFile << "\n";
	}
	cout << "finish writing " << endl;
}

void write_csvf(string filename, vector<float>& strArray, string seq, int col)
{
	ofstream outFile(filename);
	int length = strArray.size();
	int row = length / col;

	for (int i = 0; i < row; i++) {
		string lineStr;
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
	cout << "finish writing " << endl;
}

int main(int argc, char* argv[]) {
	time_t start, end;
	double cost;
	time(&start);
	//cout << argc << endl;
	if (argc != 4) return 0;
	//cout << argv[1] << endl;
	if (argv[1][0] == 'c') {
		if (!strcmp(argv[2], "data_well_public.hxv")) {
			cout << argv[2] << endl;
			ByteArrayOutputStream out(argv[3]);
			LongDeltaEncoder encoder;
			vector<vector<long long>> strArrayll;
			read_csv(argv[2], strArrayll, ',',180000);

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

			int length = strArrayll.size();
			cout << length << endl;
			vector<ll> strArray0 = strArrayll[0];
			int width = strArray0.size();
			cout << width << endl;
			for (int i = 0; i < width; i++) {
				for (int j = 0; j < length; j++) {
					encoder.encode(strArrayll[j][i], out);
				}
			}
			encoder.flush(out);
			out.write2file();
		}
		else if (!strcmp(argv[2], "shore_public.dat")) {
			vector<vector<float>> strArrayf;
			ByteArrayOutputStream out(argv[3]);
			
			read_csv(argv[2], strArrayf, ' ',50000);

			int length = strArrayf.size();
			cout << length << endl;
			vector<float> strArray0 = strArrayf[0];
			int width = strArray0.size();
			cout << width << endl;
			for (int i = 0; i < width; i++) {
				FloatDeltaEncoder encoder;
				for (int j = 0; j < length; j++) {
					encoder.encode(strArrayf[j][i], out);
				}
				encoder.flush(out);
				out.write2file();
			}
		}
	}
	else if (argv[1][0] == 'd') {
		if (!strcmp(argv[3], "data_well_public1.hxv")) {
			cout << argv[3] << endl;		
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
			cout<< llArray.size() << endl;
			write_csvll(argv[3], llArray, ",",5);
		}
		else if (!strcmp(argv[3], "shore_public1.dat")) {
			cout << argv[3] << endl;
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
			cout << fArray.size() << endl;
			write_csvf(argv[3], fArray, " ", 71);
		}
	}
	time(&end);
	cost = difftime(end, start);
	cout << cost << endl;
	return 0;
}