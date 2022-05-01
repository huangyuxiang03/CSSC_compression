#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;


template <typename T>
void read_csv(string filename,vector<vector<T>> strArray,char seq)
{
    ifstream inFile(filename);
    string lineStr;
    cout << "the whole line is: " << endl;
    int i = 0;
    while (getline(inFile, lineStr))
    {
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
        if (i > 128) break;
        i++;
    }
    

   cout << "--------------------------------------------" << endl;
    cout << "print what we have saved in the vector: " << endl;
    for (auto s : strArray)
    {
        for (auto x : s)
        {
            cout << x << " ";
        }
        cout << endl;
    }

}
int main() {
    vector<vector<long long>> strArrayll;
    vector<vector<float>> strArrayf;
    read_csv("C:\\Users\\xiaoj\\Desktop\\data_well_public.hxv", strArrayll,',');
    read_csv("C:\\Users\\xiaoj\\Desktop\\shore_public.dat", strArrayf, ' ');
    return 0;
}