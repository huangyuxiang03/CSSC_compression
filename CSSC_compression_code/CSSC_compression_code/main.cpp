#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

void read_csv(string filename)
{
    ifstream inFile(filename);
    string lineStr;
    vector<vector<long long>> strArray;
    cout << "the whole line is: " << endl;
    int i = 0;
    while (getline(inFile, lineStr))
    {
        cout << lineStr << endl;
        stringstream ss(lineStr);
        string str;
        long str2long;
        vector<long long> lineArray;
        while (getline(ss, str, ','))
        {
            stringstream strIn;
            strIn << str;
            long long llNum;
            strIn >> std::hex >> llNum;
            lineArray.push_back(llNum);
        }
        strArray.push_back(lineArray);
        if (i > 128) break;
        i++;
    }
    

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
int main() {

    read_csv("C:\\Users\\xiaoj\\Desktop\\data_well_public.hxv");
	return 0;
}