#include "NumberObject.h"

NumberObject::NumberObject()
{
	fract.numerator = "0";
	fract.denominator = "1";
	positive = true;
}

NumberObject::NumberObject(string str)
{
	fract.numerator = str;
	fract.denominator = "1";
	positive = true;
}

NumberObject::NumberObject(string str, bool pos)
{
	fract.numerator = str;
	fract.denominator = "1";
	positive = pos;
}

int NumberObject::find_rparenthesis(string str)   //找右括號的位置
{
	int count = 1;
	for (int i = 1; i < str.length(); i++) {
		if (str[i] == '(')
			count++;
		else if (str[i] == ')')
			count--;
		if (count == 0) {
			return i - 3;
		}
	}
	return -1;   //找不到
}

int NumberObject::getNumeratorSize()
{
	return fract.numerator.size();
}

int NumberObject::getDenominatorSize()
{
	return fract.denominator.size();
}
