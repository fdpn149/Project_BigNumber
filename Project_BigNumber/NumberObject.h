#include <iostream>
using namespace std;
class NumberObject
{
public:
	string value;
	bool positive;
	NumberObject();
	NumberObject(string str);
	NumberObject(string str, bool pos);
	int find_rparenthesis(string str);   //§ä¥k¬A¸¹ªº¦ì¸m
	bool isAllDigit(string input);
};