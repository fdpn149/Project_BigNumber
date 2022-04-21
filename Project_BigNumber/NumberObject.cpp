#include "NumberObject.h"

NumberObject::NumberObject()
{
	value = "0";
	positive = true;
}

NumberObject::NumberObject(string str)
{
	value = str;
	positive = true;
}

NumberObject::NumberObject(string str, bool pos)
{
	value = str;
	positive = pos;
}

int NumberObject::find_rparenthesis(string str)   //��k�A������m
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
	return -1;   //�䤣��
}

bool NumberObject::isAllDigit(string input)
{
	for (int i = input[0] == '-' ? 1 : 0; i < input.length(); i++) {
		if (!isdigit(input[i]))
			return false;
	}
	return true;
}