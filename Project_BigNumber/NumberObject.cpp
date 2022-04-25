#include "NumberObject.h"

map<string, NumberObject*> NumberObject::variable;

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

const int NumberObject::getNumeratorSize() const
{
	return fract.numerator.size();
}

const int NumberObject::getDenominatorSize() const
{
	return fract.denominator.size();
}

int NumberObject::inputJudge(string input)
{
	if (input == "\0")
		return 0;
	bool decimal = false;
	stringstream ss(input);
	string now_str;
	ss >> now_str;
	if (now_str == "Set") {
		ss >> now_str;
		if (now_str != "Integer" && now_str != "Decimal")
			return -2;   //��J�榡���~
		ss >> now_str;
		if (isdigit(now_str.at(0)))
			return -2;
		ss >> now_str;
		if (now_str != "=")
			return -2;
		ss >> now_str;
		string last = now_str;
		ss >> now_str;
		if (last == now_str)
			return -2;
		return 1;
	}
	short now_figure;   //�{�b���Ʀr�B�Ÿ��B�A���ζ��� (�Ʀr:1,�Ÿ�:2,�W�A��:4,�U�A��:8,����:16)
	short next_figure = 5;   //�U�@�ӥi���Ʀr�B�Ÿ��B�A���ζ��� (�Ʀr:1,�Ÿ�:2,�W�A��:4,�U�A��:8,����:16)
	int paren_count = 0;
	do {
		if (isalpha(now_str.at(0)) && (next_figure & 1) != 0) {
			now_figure = 1;
			next_figure = 26;
			map<string, NumberObject*>::iterator it = variable.find(input);
			if (it == variable.end())
				return -1;   //�䤣���ܼ�
			it = find_if(variable.begin(), variable.end(), [](pair<string, NumberObject*> m) {return m.second->dot == true; });
			if (it != variable.end())
				decimal = true;
		}
		else if (isdigit(now_str.at(0)) && (next_figure & 1) != 0) {
			now_figure = 1;
			next_figure = 26;
			bool dot = false;
			for (int i = 1; i < now_str.length(); i++)
				if (dot == false && now_str.at(i) == '.') {
					dot = true;
					decimal = true;
				}
				else if (!isdigit(now_str.at(i)))
					return -2;
		}
		else if ((now_str == "-(" || now_str == "+(" || now_str == "(") && (next_figure & 4) != 0) {
			paren_count++;
			now_figure = 4;
			next_figure = 5;
		}
		else if (now_str == ")" && (next_figure & 8) != 0) {
			if (paren_count == 0)
				return -2;
			paren_count--;
			now_figure = 8;
			next_figure = 26;
		}
		else if (now_str == "!" && (next_figure & 16) != 0) {
			now_figure = 16;
			next_figure = 26;
		}
		else if (now_str.length() > 1 && (now_str.at(0) == '-' || now_str.at(0) == '+') && (next_figure & 1) != 0) {
			now_figure = 1;
			next_figure = 26;
			bool dot = false;
			for (int i = 1; i < now_str.length(); i++) {
				if (dot == false && now_str.at(i) == '.') {
					dot = true;
					decimal = true;
				}
				else if (!isdigit(now_str.at(i)))
					return -2;
			}
		}
		else if (now_str.length() == 1 && (next_figure & 2) != 0) {
			now_figure = 2;
			next_figure = 5;
			string all = "+-*/^";
			if (find(all.begin(), all.end(), now_str[0]) == all.end())
				return -2;
		}
		else
			return -2;
	} while (ss >> now_str);

	if ((now_figure & 6) != 0)   //�p�G�̫�@�Ӧr�O�Ÿ�
		return -2;

	if (paren_count != 0)
		return -2;

	if (decimal == true)
		return 3;

	return 2;
}

int NumberObject::replaceVariables(string& input)
{
	return 0;
}

void NumberObject::printError(int err)
{
	switch (err) {
	case -2:
		cout << "��J���~" << endl; break;
	case -1:
		cout << "�t�Ƥ���}�ڸ�" << endl; break;
	case 0:
		cout << "���Ƥ��ର0" << endl; break;
	case 1:
		cout << "�t�Ƥ���ⶥ��" << endl; break;
	case 2:
		cout << "�p�Ƥ���ⶥ��" << endl; break;
	case 3:
		cout << "���ƽп�J0.5������" << endl; break;
	case 4:
		cout << "�䤣���ܼ�" << endl; break;
	}
}
