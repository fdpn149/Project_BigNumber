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
	bool dec;   //�O�_�O�p��
	bool positive;
	NumberObject();
	NumberObject(string str);
	NumberObject(string str, bool pos);
	int find_rparenthesis(string str);   //��k�A������m
	int getNumeratorSize();
	int getDenominatorSize();
};