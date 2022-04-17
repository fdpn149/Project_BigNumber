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
			return i - 3;
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
			int ss_loc = ss.tellg();   //ss�{�b���쪺��m
			int len = find_rparenthesis(input.substr(ss_loc - 1));   //��A���ҬA������
			string result = calculate(input.substr(ss_loc + 1, len));   //�A�������B�⵲�G
			number.push_back(result);   //�s�Ʀr
			input.replace(ss_loc - 1, len + 4, result);   //�N�A�����������G
			ss.str(input);   //���ss����
			ss.seekg(ss_loc + result.length()-1);   //�Nss������m�]�^��
		}
		else if (now_str[0] == '+' && now_str[1] == '(') {   //���A��
			int ss_loc = ss.tellg();
			int len = find_rparenthesis(input.substr(ss_loc + 1));   //��A���ҬA������
			string result = calculate(input.substr(ss_loc + 1, len + 2));
			number.push_back(result);   //�s�Ʀr
			input.replace(ss_loc - 2, len + 7, result);   //�N�A�����������G
			ss.str(input);   //���ss����
			ss.seekg(ss_loc + result.length()-1);   //�Nss������m�]�^��
		}
		else if (now_str[0] == '-' && now_str[1] == '(') {   //�t�A��
			int ss_loc = ss.tellg();
			int len = find_rparenthesis(input.substr(ss_loc + 1));   //��A���ҬA������
			string result = '-' + calculate(input.substr(ss_loc + 1, len + 2));
			number.push_back(result);   //�s�Ʀr
			input.replace(ss_loc - 2, len + 7, result);   //�N�A�����������G
			ss.str(input);   //���ss����
			ss.seekg(ss_loc + result.length()-1);   //�Nss������m�]�^��
		}
		else if (now_str[0] == ')') {   //�ϬA��

		}
		else if (isalpha(now_str[0])) {   //�ܼ�

		}
		else if (isdigit(now_str[0])) {   //���
			number.push_back(now_str);
		}
		else if ((now_str[0] == '+' || now_str[0] == '-') && now_str.length() > 1) {   //���t��
			number.push_back(now_str);
		}
		else {   //�Ÿ�
			symbol.push_back(now_str[0]);
		}
	}
	return split_calculate(number, symbol);
}

string Integer::split_calculate(vector<string> &number, vector<char> &symbol)
{
	/*(�@��t�����B�z)*/

	//�����p��
	for (int i = 0; i < symbol.size(); i++) {
		if (symbol[i] == '!') {   //�Y�J�춥��
			Integer num = number[i];
			number[i] = !num;
			symbol.erase(symbol.begin() + i);
			i--;
		}
	}

	//����B��
	for (int i = 0; i < symbol.size(); i++) {
		if (symbol[i] == '^') {   //�Y�J�즸��
			Integer num1 = number[i];
			Integer num2 = number[i + 1];
			number[i] = num1 ^ num2;
			number.erase(number.begin() + i + 1);
			symbol.erase(symbol.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < symbol.size(); i++) {
		if (symbol[i] == '*') {   //�Y�J�쭼
			Integer num1 = number[i];
			Integer num2 = number[i + 1];
			number[i] = num1 * num2;
			number.erase(number.begin() + i + 1);
			symbol.erase(symbol.begin() + i);
			i--;
			continue;
		}
		if (symbol[i] == '/') {   //�Y�J�찣
			Integer num1 = number[i];
			Integer num2 = number[i + 1];
			number[i] = num1 / num2;
			number.erase(number.begin() + i + 1);
			symbol.erase(symbol.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < symbol.size(); i++) {
		if (symbol[i] == '+') {   //�Y�J��[
			Integer num1 = number[i];
			Integer num2 = number[i + 1];
			number[i] = num1 + num2;
			number.erase(number.begin() + i + 1);
			symbol.erase(symbol.begin() + i);
			i--;
			continue;
		}
		if (symbol[i] == '-') {   //�Y�J���
			Integer num1 = number[i];
			Integer num2 = number[i + 1];
			number[i] = num1 - num2;
			number.erase(number.begin() + i + 1);
			symbol.erase(symbol.begin() + i);
			i--;
		}
	}
	return number[0];
}

bool Integer::isAllDigit(string input)
{
	for (int i = input[0] == '-' ? 1 : 0; i < input.length(); i++) {
		if (!isdigit(input[i]))
			return false;
	}
	return true;
}

Integer::Integer(string str)
{
	if (isAllDigit(str))
		value = str;
	else
		value = calculate(str);
}

const string Integer::operator!() const
{
	return "9191";
}

const string Integer::operator^(const Integer& num) const
{
	return "7474";
}

const string Integer::operator*(const Integer& num) const
{
	return "7272";
}

const string Integer::operator/(const Integer& num) const
{
	return "7575";
}

const string Integer::operator+(const Integer& num) const
{
	return "9292";
}

const string Integer::operator-(const Integer& num) const
{
	return "7112";
}

ostream& operator<<(ostream& outputStream, Integer& numObj)
{
	cout << numObj.value;
	return outputStream;
}
