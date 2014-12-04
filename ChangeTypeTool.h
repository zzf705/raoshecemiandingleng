#pragma once
#include <map>
#pragma once
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class ChangeTypeTool{
public :
	//simple type change
	static int stringToInt(string str);
	static double stringToDouble(string str);
	static char* stringToChar(string str);
	static const char* stringToConstChar(string str);
	static string constCharToString(const char* c);
	static string intToString(int i);
	static string doubleToString(double d);

	//string to map vector
	static vector<map<int,double>> stringToIntMapVector(string str,string sepOut,string sepIn);
	static vector<map<string,double>> stringToStringMapVector(string str,string sepOut,string sepIn);
	static vector<map<double,double>> stringToDoubleMapVector(string str,string sepOut,string sepIn);
	//static vector<map<int,double>> stringToVectorMap(string str,string sep);

	//string to map
	static map<int,double> stringToIntMap(string str,string sep);
	static map<string,double> stringToStringMap(string str,string sep);
	static map<double,double> stringToDoubleMap(string str,string sep);

	//string to vector   都是外部用;内部用：
	static vector<string> stringToStringVector(string str,string sep);
	static vector<int> stringToIntVector(string str,string sep);

	//vector to string
	static string vectorToString(vector<int> intVector);


	//string split   这个是真正实现字符串分割的方法
	static vector<string> strSplit(string str,string sep);
	//static vector<string> strFSplit(string str);

	

	//static map<int,double> stringToMap(string str,string sep);
	
};
