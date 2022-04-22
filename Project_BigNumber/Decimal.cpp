#include "NumberObject.h"
#include "Decimal.h"
#include "Integer.h"

Decimal Decimal::calculate(string input)
{
	stringstream ss(input);
	string now_str;
	vector<char> symbol;   //存符號
	vector<Decimal> number;   //存數字
	while (ss >> now_str) {
		if (now_str[0] == '(') {   //括號
			int ss_loc = ss.tellg();   //ss現在指到的位置
			int len = find_rparenthesis(input.substr(ss_loc - 1));   //找括號所括的長度
			Decimal result_d = calculate(input.substr(ss_loc + 1, len));   //括號中的運算結果
			string result = "(" + result_d.fract.numerator + "/" + result_d.fract.denominator + ")";   //轉成分數
			number.push_back(result_d);   //存數字
			input.replace(ss_loc - 1, len + 4, result);   //將括號替換成結果
			ss.str(input);   //更改ss的值
			ss.seekg(ss_loc + result.length() - 1);   //將ss指的位置設回來
		}
		else if (now_str[0] == '+' && now_str[1] == '(') {   //正 括號
			int ss_loc = ss.tellg();
			int len = find_rparenthesis(input.substr(ss_loc + 1));   //找括號所括的長度
			Decimal result_d = calculate(input.substr(ss_loc + 1, len + 2));   //括號中的運算結果
			string result = "(" + result_d.fract.numerator + "/" + result_d.fract.denominator + ")";   //轉成分數
			number.push_back(result_d);   //存數字
			input.replace(ss_loc - 2, len + 7, result);   //將括號替換成結果
			ss.str(input);   //更改ss的值
			ss.seekg(ss_loc + result.length() - 1);   //將ss指的位置設回來
		}
		else if (now_str[0] == '-' && now_str[1] == '(') {   //負 括號
			int ss_loc = ss.tellg();
			int len = find_rparenthesis(input.substr(ss_loc + 1));   //找括號所括的長度
			Decimal result_d = calculate(input.substr(ss_loc + 1, len + 2));   //括號中的運算結果
			result_d.positive = false;   //設成負
			string result = "-(" + result_d.fract.numerator + "/" + result_d.fract.denominator + ")";   //轉成分數
			number.push_back(result_d);   //存數字
			input.replace(ss_loc - 2, len + 7, result);   //將括號替換成結果
			ss.str(input);   //更改ss的值
			ss.seekg(ss_loc + result.length() - 1);   //將ss指的位置設回來
		}
		else if (isalpha(now_str[0])) {   //變數

		}
		else if (isdigit(now_str[0])) {   //小數
			Decimal d = now_str;
			number.push_back(d);
		}
		else if ((now_str[0] == '+' || now_str[0] == '-') && now_str.length() > 1) {   //正負數
			Decimal d = now_str;
			number.push_back(d);
		}
		else {   //符號
			symbol.push_back(now_str[0]);
		}
	}
	return split_calculate(number, symbol);
}

Decimal Decimal::split_calculate(vector<Decimal>& number, vector<char>& symbol)
{
	/*(一堆負號的處理)*/

	//階乘計算
	for (int i = 0; i < symbol.size(); i++) {
		if (symbol[i] == '!') {   //若遇到階乘
			Decimal num = number[i];
			number[i] = !num;
			symbol.erase(symbol.begin() + i);
			i--;
		}
	}

	//次方運算
	for (int i = 0; i < symbol.size(); i++) {
		if (symbol[i] == '^') {   //若遇到次方
			Decimal num1 = number[i];
			Decimal num2 = number[i + 1];
			number[i] = num1 ^ num2;
			number.erase(number.begin() + i + 1);
			symbol.erase(symbol.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < symbol.size(); i++) {
		if (symbol[i] == '*') {   //若遇到乘
			Decimal num1 = number[i];
			Decimal num2 = number[i + 1];
			number[i] = num1 * num2;
			number.erase(number.begin() + i + 1);
			symbol.erase(symbol.begin() + i);
			i--;
			continue;
		}
		if (symbol[i] == '/') {   //若遇到除
			Decimal num1 = number[i];
			Decimal num2 = number[i + 1];
			number[i] = num1 / num2;
			number.erase(number.begin() + i + 1);
			symbol.erase(symbol.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < symbol.size(); i++) {
		if (symbol[i] == '+') {   //若遇到加
			Decimal num1 = number[i];
			Decimal num2 = number[i + 1];
			number[i] = num1 + num2;
			number.erase(number.begin() + i + 1);
			symbol.erase(symbol.begin() + i);
			i--;
			continue;
		}
		if (symbol[i] == '-') {   //若遇到減
			Decimal num1 = number[i];
			Decimal num2 = number[i + 1];
			number[i] = num1 - num2;
			number.erase(number.begin() + i + 1);
			symbol.erase(symbol.begin() + i);
			i--;
		}
	}
	return number[0];
}

bool Decimal::isPureNum(string input)
{
	bool dot = false;
	if (input[0] == '-') {
		if (input[1] == '.')
			return false;
		for (int i = 1; i < input.length(); i++) {
			if (!isdigit(input[i])) {
				if (input[i] == '.' && dot == false) {
					dot = true;
				}
				else
					return false;
			}
		}
	}
	else {
		if (input[0] == '.')
			return false;
		else {
			for (int i = 0; i < input.length(); i++) {
				if (!isdigit(input[i])) {
					if (input[i] == '.' && dot == false) {
						dot = true;
					}
					else
						return false;
				}
			}
		}
	}
	return true;
}

int Decimal::countDecimalPlace(string str)
{
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '.')
			return str.length() - i - 1;
	}
	return -1;
}

void Decimal::toIrreducible(fraction& f) const
{
	if (f.denominator == "1")
		return;

	while (f.numerator[0] == '0' && f.numerator.length() > 1)   //清開頭的0
		f.numerator.erase(0, 1);

	if (f.numerator == "0") {
		f.denominator = "1";
		return;
	}
	Integer a = f.numerator;
	Integer b = f.denominator;
	Integer g = gcd(a, b);
	a = a / g;
	b = b / g;
	f.numerator = a.fract.numerator;
	f.denominator = b.fract.numerator;
}

const Integer Decimal::gcd(Integer a, Integer b) const
{
	Integer c;
	while (b.fract.numerator != "0") {
		c = a % b;
		a = b;
		b = c;
	}
	return a;
}

const string Decimal::findExactlyValue()
{
	string denominator = this->fract.denominator;
	string numerator = this->fract.numerator;

	Integer num = denominator;

	map<int, Integer> products;
	products[0] = "0";
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

	int dot;
	int pos = denominator.length() - 1;
	int times;
	string quotient;
	Integer remainder;
	if (numerator.length() < denominator.length()) {   //如果分母的位數多於分子
		dot = 1;   //小數點設在第1位
		remainder = numerator;
		remainder.fract.numerator.append(denominator.length() - numerator.length(), '0');
		quotient.append(denominator.length() - 1, '0');
	}
	else {
		remainder = numerator.substr(0, denominator.length());
		dot = numerator.length() - denominator.length() + 1;   //小數點位置
	}
	int i;
	for(i = 0; i <= 100 - denominator.length() + numerator.length(); i++){
		int n = 1;
		while (products[n] <= remainder)
			n++;
		n--;
		quotient.append(to_string(n));
		remainder = remainder - products[n];

		if (remainder.fract.numerator == "0" && pos >= numerator.length())   //除完了
			break;

		if (remainder.fract.numerator[0] == '0')   //清開頭的0
			remainder.fract.numerator.erase(0, 1);

		pos++;
		if (pos < numerator.length())
			remainder.fract.numerator.append(string(1, numerator[pos]));
		else
			remainder.fract.numerator.append("0");
	}
	quotient.insert(dot, ".");
	while (quotient[0] == '0' && quotient[1] != '.')   //清開頭的0
		quotient.erase(0, 1);

	if(99 - i + dot > 0)
		quotient.append(99 - i + dot, '0');
	return quotient;
}

Decimal::Decimal() : NumberObject()
{
	fract.numerator = "0";
	fract.denominator = "1";
}

Decimal::Decimal(const string str) : NumberObject()
{
	fract.numerator = str;
	positive = fract.numerator[0] == '-' ? false : true;   //是否是負數
	fract.numerator = positive ? fract.numerator : fract.numerator.substr(1);   //去掉負號
	int place = countDecimalPlace(str);   //找小數點的位置
	if (place != -1) {   //如果有找到小數點
		dec = true;
		string noDot = fract.numerator;
		string::iterator it = find(noDot.begin(), noDot.end(), '.');
		noDot.erase(it);   //去掉小數點
		fract.numerator = noDot;   //分子設為去掉小數點的值
		fract.denominator = "1";   //分母先設為1
		fract.denominator.append(place, '0');   //分母後面加上0
		toIrreducible(fract);
	}
	else {   //如果是整數
		dec = false;
		fract.denominator = "1";
	}
}

Decimal::Decimal(const char* str) : NumberObject()
{
	if (isPureNum(str)) {   //是不是一個數 還是算式
		dec = true;
		fract.numerator = str;
		positive = fract.numerator[0] == '-' ? false : true;   //是否是負數
		fract.numerator = positive ? fract.numerator : fract.numerator.substr(1);   //去掉負號
		int place = countDecimalPlace(str);   //找小數點的位置
		if (place != -1) {   //如果有找到小數點
			string noDot = fract.numerator;
			string::iterator it = find(noDot.begin(), noDot.end(), '.');
			noDot.erase(it);   //去掉小數點
			fract.numerator = noDot;   //分子設為去掉小數點的值
			fract.denominator = "1";   //分母先設為1
			fract.denominator.append(place, '0');   //分母後面加上0
			toIrreducible(fract);
		}
		else {   //如果是整數
			dec = false;
			fract.denominator = "1";
		}
	}
	else {
		Decimal d = calculate(str);
		fract = d.fract;
		positive = d.positive;
	}
}

const Decimal Decimal::operator!() const
{
	return Decimal();
}

const Decimal Decimal::operator^(const Decimal& num) const
{
	return Decimal();
}

const Decimal Decimal::operator*(const Decimal& num) const
{
	Integer d1(fract.denominator);   //分母1
	Integer n1(fract.numerator);   //分子1
	Integer d2(num.fract.denominator);   //分母2
	Integer n2(num.fract.numerator);   //分子2
	Decimal result;
	result.fract.numerator = (n1 * n2).tostring();
	result.fract.denominator = (d1 * d2).tostring();
	if (!this->positive != !num.positive)
		result.positive = false;
	toIrreducible(result.fract);
	return result;
}

const Decimal Decimal::operator/(const Decimal& num) const
{
	Integer n1(fract.numerator);   //分子1
	Integer n2(num.fract.numerator);   //分子2
	Decimal result;
	if (this->dec == false && num.dec == false) {   //如果是兩個整數相除
		result = (n1 / n2).fract.numerator;
		if (!this->positive != !num.positive)
			result.positive = false;
		result.fract.denominator = "1";
		return result;
	}
	Integer d1(fract.denominator);   //分母1
	Integer d2(num.fract.denominator);   //分母2
	result.fract.numerator = (n1 * d2).tostring();
	result.fract.denominator = (d1 * n2).tostring();
	if (!this->positive != !num.positive)
		result.positive = false;
	toIrreducible(result.fract);
	return result;
}

const Decimal Decimal::operator+(const Decimal& num) const
{
	Integer d1(fract.denominator);   //分母1
	Integer n1(fract.numerator);   //分子1
	Integer d2(num.fract.denominator);   //分母2
	Integer n2(num.fract.numerator);   //分子2
	Integer r;
	Decimal result;
	n1.positive = this->positive;
	n2.positive = num.positive;
	if (d1 == d2) {
		r = n1 + n2;
		result.fract.denominator = d1.tostring();
		result.fract.numerator = r.fract.numerator;
		result.positive = r.positive;
		toIrreducible(result.fract);
		return result;
	}
	Integer g = gcd(d1, d2);
	n1 = n1 * d2 / g;   //通分後的分子1
	n2 = n2 * d1 / g;   //通分後的分子2
	d1 = d1 * d2 / g;   //通分後的分母
	r = n1 + n2;
	result.fract.denominator = d1.tostring();
	result.fract.numerator = r.fract.numerator;
	result.positive = r.positive;
	toIrreducible(result.fract);
	return result;
}

const Decimal Decimal::operator-(const Decimal& num) const
{
	Integer d1(fract.denominator);   //分母1
	Integer n1(fract.numerator);   //分子1
	Integer d2(num.fract.denominator);   //分母2
	Integer n2(num.fract.numerator);   //分子2
	Integer r;
	Decimal result;
	n1.positive = this->positive;
	n2.positive = num.positive;
	if (d1 == d2) {
		r = n1 - n2;
		result.fract.denominator = d1.tostring();
		result.fract.numerator = r.fract.numerator;
		result.positive = r.positive;
		toIrreducible(result.fract);
		return result;
	}
	Integer g = gcd(d1, d2);
	n1 = n1 * d2 / g;   //通分後的分子1
	n2 = n2 * d1 / g;   //通分後的分子2
	d1 = d1 * d2 / g;   //通分後的分母
	r = n1 - n2;
	result.fract.denominator = d1.tostring();
	result.fract.numerator = r.fract.numerator;
	result.positive = r.positive;
	toIrreducible(result.fract);
	return result;
}

ostream& operator<<(ostream& outputStream, Decimal& numObj)
{
	cout << (numObj.positive ? "" : "-") << numObj.findExactlyValue();
	return outputStream;
}
