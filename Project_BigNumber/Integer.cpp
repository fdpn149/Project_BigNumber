#include "Integer.h"

int Integer::find_rparenthesis(string str)   //找右括號的位置
{
	int count = 1;
	for (int i = 1; i < str.length(); i++) {
		if (str[i] == '(')
			count++;
		else if (str[i] == ')')
			count--;
		if (count == 0) {
			return i - 1;
		}
	}
	return -1;   //找不到
}

void Integer::process(string str)
{
	value = calculate(str);
}

string Integer::calculate(string input)
{
	stringstream ss(input);
	string now_str;
	vector<char> symbol;   //存符號
	vector<string> number;   //存數字
	while (ss >> now_str) {
		if (now_str[0] == '(') {   //括號
			cout << input.substr(ss.tellp(), 5) << endl;
			int len = find_rparenthesis(input.substr(ss.tellp()));   //找括號所括的長度
			number.push_back(calculate(input.substr(ss.tellp(), len)));
		}
		else if (now_str[0] == ')') {   //反括號

		}
		else if (isalpha(now_str[0])) {   //變數

		}
		else if (isdigit(now_str[0]) || now_str[0] == '-') {   //整數

		}
		else {   //符號

		}
	}
	return "";
}

Integer::Integer(string str)
{
	calculate(str);
}

ostream& operator<<(ostream& outputStream, Integer& numObj)
{
	cout << numObj.value;
	return outputStream;
}
