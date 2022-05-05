#pragma once
#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "ByteArrayOutputStream.h"
#include "LongDeltaEncoder.h"
#include "LongDeltaDecoder.h"
using namespace std;

template <typename T>
void read_csv(string filename, vector<vector<T>>& strArray, char seq)
{
	ifstream inFile(filename);
	string lineStr;
	cout << "read data: " << endl;
	int i = 0;
	while (getline(inFile, lineStr))
	{
		if (i > 18000) break;
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
void write_csv(string filename, vector<T>& strArray, string seq, int col)
{
	ofstream outFile(filename);
	int length = strArray.size();
	int row = length / col;
	
	for (int i = 0; i < row; i++) {
		string lineStr;
		int j = 0;
		for (; j < col - 1; j++) {
			outFile << std::hex << strArray[j * row + i];
			outFile << seq;
		}
		//cout << strArray[j * row + i] << endl;
		outFile << std::hex << strArray[j * row + i];
		outFile << "\n";
	}
	//int i = 0;
	//while (getline(inFile, lineStr))
	//{
	//	if (i > 5000) break;
	//	i++;
	//	//cout << lineStr << endl;
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
	//		lineArray.push_back(llNum);
	//	}
	//	strArray.push_back(lineArray);
	//}
	cout << "finish writing " << endl;
}
int main(int argc, char* argv[]) {
	time_t start, end;
	double cost;


	//cout << argc << endl;
	if (argc != 4) return 0;
	//cout << argv[1] << endl;
	if (argv[1][0] == 'c') {
		//cout << strcmp(argv[2], "data_well_public.hxv") << endl;
		if (!strcmp(argv[2], "data_well_public.hxv")) {
			cout << argv[2] << endl;
			int length = 0;
			vector<vector<long long>> strArrayll;
			read_csv(argv[2], strArrayll, ',');
			vector<vector<long long>> resArray = transpose(strArrayll);
			ByteArrayOutputStream out(argv[3]);
			LongDeltaEncoder encoder;
			//LongDeltaDecoder decoder;
			time(&start);

			for (vector<long long> perArrayll : resArray) {
				for (ll num : perArrayll) {
					encoder.encode(num, out);
				}
			}
			cout << resArray[0].size() << endl;
			time(&end);
			cost = difftime(end, start);
			//cout << cost << endl;
			//cout << "out" << endl;
			encoder.flush(out);
			//cout << out.getBytes().size() << endl;
			out.write2file();
			//ByteBuffer in(out.getBytes());
			//for (int j = 0; j < 2000; j++) {
			//    ll r = decoder.readLong(in);
			//}
			//bool a = decoder.hasNext(in);
		}
		else if (!strcmp(argv[2], "shore_public.dat")) {
			vector<vector<float>> strArrayf;
			read_csv(argv[2], strArrayf, ' ');
			vector<vector<float>> resArray = transpose(strArrayf);
			ByteArrayOutputStream out(argv[3]);
			LongDeltaEncoder encoder;
			//LongDeltaDecoder decoder;
			time(&start);

			for (vector<float> perArrayll : resArray) {
				for (ll num : perArrayll) {
					encoder.encode(num, out);
				}
			}
			time(&end);
			cost = difftime(end, start);
			cout << cost << endl;
			//cout << "out" << endl;
			encoder.flush(out);
			cout << out.getBytes().size() << endl;
			out.write2file();
		}
	}
	else if (argv[1][0] == 'd') {

		if (!strcmp(argv[3], "data_well_public1.hxv")) {
			cout << argv[3] << endl;
			//int length = 0;
			vector<vector<long long>> strArrayll;
			//read_csv(argv[2], strArrayll, ',');
			
			ByteArrayOutputStream out(argv[2]);
			//LongDeltaEncoder encoder;
			LongDeltaDecoder decoder;
			
			time(&start);
			out.readFromFile();
			ByteBuffer in(out.getBytes());
			int length = out.getBytes().size();
			vector<long long> llArray;
			while(in.remaining()!=0) {
			    ll r = decoder.readLong(in);
				//cout << r << endl;
				llArray.push_back(r);
			}
			cout<< llArray.size() << endl;
			write_csv(argv[3], llArray, ",",5);
			//vector<vector<long long>> resArray = transpose(strArrayll);
			//bool a = decoder.hasNext(in);
		}
		else if (!strcmp(argv[3], "shore_public1.dat")) {
			vector<vector<float>> strArrayf;
			read_csv(argv[2], strArrayf, ' ');
			vector<vector<float>> resArray = transpose(strArrayf);
			ByteArrayOutputStream out(argv[3]);
			LongDeltaEncoder encoder;
			//LongDeltaDecoder decoder;
			time(&start);

			for (vector<float> perArrayll : resArray) {
				for (ll num : perArrayll) {
					encoder.encode(num, out);
				}
			}
			time(&end);
			cost = difftime(end, start);
			cout << cost << endl;
			cout << "out" << endl;
			//encoder.flush(out);
			cout << out.getBytes().size() << endl;
			out.write2file();
		}
	}

	return 0;
}