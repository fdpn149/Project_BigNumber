#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include <cctype>
#include <map>
using namespace std;

struct fraction {
	string numerator;
	string denominator;
};

class NumberObject
{
public:
	static map<string,NumberObject*> variable;
	fraction fract;
	bool dec;   //是否是小數
	bool dot;   //是否保留小數
	bool positive;
	NumberObject();
	NumberObject(string str);
	NumberObject(string str, bool pos);
	int find_rparenthesis(string str);   //找右括號的位置
	const int getNumeratorSize() const;
	const int getDenominatorSize() const;
	static int inputJudge(string input);
	static void setVariables(string& input);
	static void replaceVariables(string& input);
	static void printError(int err);
};