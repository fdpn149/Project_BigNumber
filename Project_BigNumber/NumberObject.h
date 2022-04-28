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
	bool dec;   //�O�_�O�p��
	bool dot;   //�O�_�O�d�p��
	bool positive;
	NumberObject();
	NumberObject(string str);
	NumberObject(string str, bool pos);
	int find_rparenthesis(string str);   //��k�A������m
	const int getNumeratorSize() const;
	const int getDenominatorSize() const;
	static int inputJudge(string input);
	static void setVariables(string& input);
	static void replaceVariables(string& input);
	static void printError(int err);
};