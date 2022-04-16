#include "Integer.h"

int Integer::find_rparenthesis(string str)   //��k�A������m
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
	return -1;   //�䤣��
}

void Integer::process(string str)
{
	value = calculate(str);
}

string Integer::calculate(string input)
{
	stringstream ss(input);
	string now_str;
	vector<char> symbol;   //�s�Ÿ�
	vector<string> number;   //�s�Ʀr
	while (ss >> now_str) {
		if (now_str[0] == '(') {   //�A��
			cout << input.substr(ss.tellp(), 5) << endl;
			int len = find_rparenthesis(input.substr(ss.tellp()));   //��A���ҬA������
			number.push_back(calculate(input.substr(ss.tellp(), len)));
		}
		else if (now_str[0] == ')') {   //�ϬA��

		}
		else if (isalpha(now_str[0])) {   //�ܼ�

		}
		else if (isdigit(now_str[0]) || now_str[0] == '-') {   //���

		}
		else {   //�Ÿ�

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
