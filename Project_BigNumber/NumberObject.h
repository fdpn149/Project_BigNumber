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
	fraction fract;
	bool dec;   //是否是小數
	bool positive;
	NumberObject();
	NumberObject(string str);
	NumberObject(string str, bool pos);
	int find_rparenthesis(string str);   //找右括號的位置
	int getNumeratorSize();
	int getDenominatorSize();
};