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
			return i - 3;
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
			int ss_loc = ss.tellg();   //ss現在指到的位置
			int len = find_rparenthesis(input.substr(ss_loc - 1));   //找括號所括的長度
			string result = calculate(input.substr(ss_loc + 1, len));   //括號中的運算結果
			number.push_back(result);   //存數字
			input.replace(ss_loc - 1, len + 4, result);   //將括號替換成結果
			ss.str(input);   //更改ss的值
			ss.seekg(ss_loc + result.length()-1);   //將ss指的位置設回來
		}
		else if (now_str[0] == '+' && now_str[1] == '(') {   //正括號
			int ss_loc = ss.tellg();
			int len = find_rparenthesis(input.substr(ss_loc + 1));   //找括號所括的長度
			string result = calculate(input.substr(ss_loc + 1, len + 2));
			number.push_back(result);   //存數字
			input.replace(ss_loc - 2, len + 7, result);   //將括號替換成結果
			ss.str(input);   //更改ss的值
			ss.seekg(ss_loc + result.length()-1);   //將ss指的位置設回來
		}
		else if (now_str[0] == '-' && now_str[1] == '(') {   //負括號
			int ss_loc = ss.tellg();
			int len = find_rparenthesis(input.substr(ss_loc + 1));   //找括號所括的長度
			string result = '-' + calculate(input.substr(ss_loc + 1, len + 2));
			number.push_back(result);   //存數字
			input.replace(ss_loc - 2, len + 7, result);   //將括號替換成結果
			ss.str(input);   //更改ss的值
			ss.seekg(ss_loc + result.length()-1);   //將ss指的位置設回來
		}
		else if (isalpha(now_str[0])) {   //變數

		}
		else if (isdigit(now_str[0])) {   //整數
			number.push_back(now_str);
		}
		else if ((now_str[0] == '+' || now_str[0] == '-') && now_str.length() > 1) {   //正負數
			number.push_back(now_str);
		}
		else {   //符號
			symbol.push_back(now_str[0]);
		}
	}
	return split_calculate(number, symbol);
}

string Integer::split_calculate(vector<string> &number, vector<char> &symbol)
{
	/*(一堆負號的處理)*/

	//階乘計算
	for (int i = 0; i < symbol.size(); i++) {
		if (symbol[i] == '!') {   //若遇到階乘
			Integer num = number[i];
			number[i] = !num;
			symbol.erase(symbol.begin() + i);
			i--;
		}
	}

	//次方運算
	for (int i = 0; i < symbol.size(); i++) {
		if (symbol[i] == '^') {   //若遇到次方
			Integer num1 = number[i];
			Integer num2 = number[i + 1];
			number[i] = num1 ^ num2;
			number.erase(number.begin() + i + 1);
			symbol.erase(symbol.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < symbol.size(); i++) {
		if (symbol[i] == '*') {   //若遇到乘
			Integer num1 = number[i];
			Integer num2 = number[i + 1];
			number[i] = num1 * num2;
			number.erase(number.begin() + i + 1);
			symbol.erase(symbol.begin() + i);
			i--;
			continue;
		}
		if (symbol[i] == '/') {   //若遇到除
			Integer num1 = number[i];
			Integer num2 = number[i + 1];
			number[i] = num1 / num2;
			number.erase(number.begin() + i + 1);
			symbol.erase(symbol.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < symbol.size(); i++) {
		if (symbol[i] == '+') {   //若遇到加
			Integer num1 = number[i];
			Integer num2 = number[i + 1];
			number[i] = num1 + num2;
			number.erase(number.begin() + i + 1);
			symbol.erase(symbol.begin() + i);
			i--;
			continue;
		}
		if (symbol[i] == '-') {   //若遇到減
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



Integer::Integer(const string str)
{
	value = str;
}

Integer::Integer(const char* str)
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
	bool negativeA = this->value[0] == '-' ? true : false;   //是否是負數
	bool negativeB = num.value[0] == '-' ? true : false;   //是否是負數
	string numA, numB;
	numA = negativeA ? this->value.substr(1) : this->value;   //去掉負號
	numB = negativeB ? num.value.substr(1) : num.value;   //去掉負號

	if ((negativeA ^ negativeB) == false) {   //同號
		if (numA.size() < numB.size())
			numA.insert(numA.begin(), numB.size() - numA.size(), '0');   //補0
		else if(numA.size() > numB.size())
			numB.insert(numB.begin(), numA.size() - numB.size(), '0');   //補0
		bool over = false;   //進位
		for (int i = numA.size() - 1; i >= 0; i--) {
			numA[i] += numB[i] + over - 48;
			over = false;
			if (numA[i] > '9') {
				over = true;
				numA[i] -= 10;
			}
		}
		if (over)
			numA.insert(numA.begin(), '1');
		if (negativeA)
			numA.insert(numA.begin(), '-');
		return numA;
	}
	else if (!negativeA) {   //A+(-B)
		return *this - Integer(numB);
	}
	else {   //(-A)+B
		return num - Integer(numA);
	}
}

const string Integer::operator-(const Integer& num) const
{
	bool negativeA = this->value[0] == '-' ? true : false;   //是否是負數
	bool negativeB = num.value[0] == '-' ? true : false;   //是否是負數
	string numA, numB;
	numA = negativeA ? this->value.substr(1) : this->value;   //去掉負號
	numB = negativeB ? num.value.substr(1) : num.value;   //去掉負號

	if ((negativeA ^ negativeB) == false) {   //同號
		if (negativeA)   //(-A)-(-B)
			numA.swap(numB);   //改成B-A
		if (numA.size() < numB.size())
			numA.insert(numA.begin(), numB.size() - numA.size(), '0');   //補0
		else if (numA.size() > numB.size())
			numB.insert(numB.begin(), numA.size() - numB.size(), '0');   //補0
		bool inverse;
		if (numA < numB) {   //A < B
			inverse = true;
			numA.swap(numB);
		}
		else   //A > B
			inverse = false;

		for (int i = 0; i < numA.size(); i++) {
			numA[i] -= numB[i] - '0';
			if (numA[i] < '0') {
				for (int j = i; j >= 1; j--) {
					numA[j] += 10;
					numA[j - 1] -= 1;
					if (numA[j - 1] >= '0')
						break;
				}
			}
		}

		for (int i = 0; i < numA.size(); i++) {
			if (numA[i] == '0') {
				numA.erase(numA.begin() + i);
				i--;
			}
			else
				break;
		}

		if (numA.size() == 0)
			numA = "0";

		if (inverse)
			return '-' + numA;
		else
			return numA;
	}
	else if (!negativeA) {   //A-(-B)
		return *this + Integer(numB);
	}
	else {   //(-A)-B
		return '-' + (num + Integer(numA));
	}
}

ostream& operator<<(ostream& outputStream, Integer& numObj)
{
	cout << numObj.value;
	return outputStream;
}
