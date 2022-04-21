#include "NumberObject.h"
#include "Integer.h"

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
		else if (now_str[0] == '+' && now_str[1] == '(') {   //正 括號
			int ss_loc = ss.tellg();
			int len = find_rparenthesis(input.substr(ss_loc + 1));   //找括號所括的長度
			string result = calculate(input.substr(ss_loc + 1, len + 2));
			number.push_back(result);   //存數字
			input.replace(ss_loc - 2, len + 7, result);   //將括號替換成結果
			ss.str(input);   //更改ss的值
			ss.seekg(ss_loc + result.length()-1);   //將ss指的位置設回來
		}
		else if (now_str[0] == '-' && now_str[1] == '(') {   //負 括號
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

Integer::Integer() : NumberObject()
{
}

Integer::Integer(const string str) : NumberObject(str)
{
	positive = value[0] == '-' ? false : true;   //是否是負數
	value = positive ? value : value.substr(1);   //去掉負號
}

Integer::Integer(const char* str) : NumberObject()
{
	if (isAllDigit(str))
		value = str;
	else
		value = calculate(str);

	positive = value[0] == '-' ? false : true;   //是否是負數
	value = positive ? value : value.substr(1);   //去掉負號
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
	map<int, Integer> products;
	products[0] = Integer();
	products[1] = *this;
	products[2] = products[1] + products[1];
	products[3] = products[1] + products[2];
	products[4] = products[2] + products[2];
	products[5] = products[2] + products[3];
	products[6] = products[3] + products[3];
	products[7] = products[3] + products[4];
	products[8] = products[4] + products[4];
	products[9] = products[4] + products[5];
	Integer sum;
	int digit = 0;
	for (int i = num.value.length() - 1; i >= 0; i--) {
		Integer b = products[num.value.at(i) - '0'];
		b.value.append(digit, '0');
		sum = sum + b;
		digit++;
	}
	if(!positive == !num.positive)
		return sum.value;
	else
		return '-' + sum.value;
}

const string Integer::operator/(const Integer& num) const
{
	if (num.value == "0") {
		cout << "除數不能為";
		return "0";
	}
	
	map<int, Integer> products;
	products[1] = num;
	products[2] = products[1] + products[1];
	products[3] = products[1] + products[2];
	products[4] = products[2] + products[2];
	products[5] = products[2] + products[3];
	products[6] = products[3] + products[3];
	products[7] = products[3] + products[4];
	products[8] = products[4] + products[4];
	products[9] = products[4] + products[5];
	products[10] = products[5] + products[5];

	Integer a;
	string originNum = value;
	string lastNum;
	string nowNum = originNum.substr(0, num.value.length()-1);
	string quotient = "0";
	string compare;
	for (int i = 0; i <= (int)value.length() - (int)num.value.length(); i++) {
		nowNum.append(to_string(originNum[num.value.size() + i-1] - '0'));
		int j = 1;
		lastNum = "0";
		compare = products[j].value;
		if (compare.length() < nowNum.length())
			compare.insert(0, 1, '0');
		while (compare.length() == nowNum.length() && compare <= nowNum) {
			lastNum = compare;
			j++;
			compare = products[j].value;
			if (compare.length() < nowNum.length())
				compare.insert(0, 1, '0');
		}
		a = Integer(nowNum) - lastNum;
		j--;
		quotient.append(to_string(j));
		nowNum = a.value;
	}
	while(quotient.length() > 1 && quotient[0] == '0')
		quotient.erase(quotient.begin());

	if (!positive == !num.positive)
		return quotient;
	else
		return '-' + quotient;
}

const string Integer::operator+(const Integer& num) const
{
	string numA, numB;
	numA = this->value;
	numB = num.value;

	if (!this->positive == !num.positive) {   //同號
		if (numA.size() < numB.size())
			numA.insert(numA.begin(), numB.size() - numA.size(), '0');   //補0
		else if(numA.size() > numB.size())
			numB.insert(numB.begin(), numA.size() - numB.size(), '0');   //補0
		bool over = false;   //進位
		for (int i = numA.size() - 1; i >= 0; i--) {
			numA[i] += numB[i] + over - 48;
			over = false;
			if (numA[i] > '9') {
				over = 1;
				numA[i] -= 10;
			}
		}
		if (over)
			numA.insert(numA.begin(), '1');
		if (!positive)
			numA.insert(numA.begin(), '-');
		return numA;
	}
	else if (positive) {   //A+(-B)
		return *this - Integer(numB);
	}
	else {   //(-A)+B
		return num - Integer(numA);
	}
}

const string Integer::operator-(const Integer& num) const
{
	string numA, numB;
	numA = this->value;
	numB = num.value;

	if (!this->positive == !num.positive) {   //同號
		if (!positive)   //(-A)-(-B)
			numA.swap(numB);   //改成B-A
		if (numA.size() < numB.size())
			numA.insert(numA.begin(), numB.size() - numA.size(), '0');   //補0
		else if (numA.size() > numB.size())
			numB.insert(numB.begin(), numA.size() - numB.size(), '0');   //補0
		bool inverse;
		if (numA < numB) {   //A < B
			inverse = 1;
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
	else if (positive) {   //A-(-B)
		return *this + Integer(numB);
	}
	else {   //(-A)-B
		return '-' + (num + Integer(numA));
	}
}

ostream& operator<<(ostream& outputStream, Integer& numObj)
{
	cout << (numObj.positive ? numObj.value : "-" + numObj.value);
	return outputStream;
}
