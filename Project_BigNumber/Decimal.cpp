#include "NumberObject.h"
#include "Decimal.h"
#include "Integer.h"

Decimal Decimal::calculate(string input)
{
	stringstream ss(input);
	string now_str;
	vector<char> symbol;   //�s�Ÿ�
	vector<Decimal> number;   //�s�Ʀr
	while (ss >> now_str) {
		if (now_str[0] == '(') {   //�A��
			int ss_loc = ss.tellg();   //ss�{�b���쪺��m
			int len = find_rparenthesis(input.substr(ss_loc - 1));   //��A���ҬA������
			Decimal result_d = calculate(input.substr(ss_loc + 1, len));   //�A�������B�⵲�G
			string result = "(" + result_d.fract.numerator + "/" + result_d.fract.denominator + ")";   //�ন����
			number.push_back(result_d);   //�s�Ʀr
			input.replace(ss_loc - 1, len + 4, result);   //�N�A�����������G
			ss.str(input);   //���ss����
			ss.seekg(ss_loc + result.length() - 1);   //�Nss������m�]�^��
		}
		else if (now_str[0] == '+' && now_str[1] == '(') {   //�� �A��
			int ss_loc = ss.tellg();
			int len = find_rparenthesis(input.substr(ss_loc + 1));   //��A���ҬA������
			Decimal result_d = calculate(input.substr(ss_loc + 1, len + 2));   //�A�������B�⵲�G
			string result = "(" + result_d.fract.numerator + "/" + result_d.fract.denominator + ")";   //�ন����
			number.push_back(result_d);   //�s�Ʀr
			input.replace(ss_loc - 2, len + 7, result);   //�N�A�����������G
			ss.str(input);   //���ss����
			ss.seekg(ss_loc + result.length() - 1);   //�Nss������m�]�^��
		}
		else if (now_str[0] == '-' && now_str[1] == '(') {   //�t �A��
			int ss_loc = ss.tellg();
			int len = find_rparenthesis(input.substr(ss_loc + 1));   //��A���ҬA������
			Decimal result_d = calculate(input.substr(ss_loc + 1, len + 2));   //�A�������B�⵲�G
			result_d.positive = false;   //�]���t
			string result = "-(" + result_d.fract.numerator + "/" + result_d.fract.denominator + ")";   //�ন����
			number.push_back(result_d);   //�s�Ʀr
			input.replace(ss_loc - 2, len + 7, result);   //�N�A�����������G
			ss.str(input);   //���ss����
			ss.seekg(ss_loc + result.length() - 1);   //�Nss������m�]�^��
		}
		else if (isalpha(now_str[0])) {   //�ܼ�

		}
		else if (isdigit(now_str[0])) {   //�p��
			Decimal d = now_str;
			number.push_back(d);
		}
		else if ((now_str[0] == '+' || now_str[0] == '-') && now_str.length() > 1) {   //���t��
			Decimal d = now_str;
			number.push_back(d);
		}
		else {   //�Ÿ�
			symbol.push_back(now_str[0]);
		}
	}
	return split_calculate(number, symbol);
}

Decimal Decimal::split_calculate(vector<Decimal>& number, vector<char>& symbol)
{
	/*(�@��t�����B�z)*/

	//�����p��
	for (int i = 0; i < symbol.size(); i++) {
		if (symbol[i] == '!') {   //�Y�J�춥��
			Decimal num = number[i];
			number[i] = !num;
			symbol.erase(symbol.begin() + i);
			i--;
		}
	}

	//����B��
	for (int i = 0; i < symbol.size(); i++) {
		if (symbol[i] == '^') {   //�Y�J�즸��
			Decimal num1 = number[i];
			Decimal num2 = number[i + 1];
			number[i] = num1 ^ num2;
			number.erase(number.begin() + i + 1);
			symbol.erase(symbol.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < symbol.size(); i++) {
		if (symbol[i] == '*') {   //�Y�J�쭼
			Decimal num1 = number[i];
			Decimal num2 = number[i + 1];
			number[i] = num1 * num2;
			number.erase(number.begin() + i + 1);
			symbol.erase(symbol.begin() + i);
			i--;
			continue;
		}
		if (symbol[i] == '/') {   //�Y�J�찣
			Decimal num1 = number[i];
			Decimal num2 = number[i + 1];
			number[i] = num1 / num2;
			number.erase(number.begin() + i + 1);
			symbol.erase(symbol.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < symbol.size(); i++) {
		if (symbol[i] == '+') {   //�Y�J��[
			Decimal num1 = number[i];
			Decimal num2 = number[i + 1];
			number[i] = num1 + num2;
			number.erase(number.begin() + i + 1);
			symbol.erase(symbol.begin() + i);
			i--;
			continue;
		}
		if (symbol[i] == '-') {   //�Y�J���
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

	while (f.numerator[0] == '0' && f.numerator.length() > 1)   //�M�}�Y��0
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
	if (numerator.length() < denominator.length()) {   //�p�G��������Ʀh����l
		dot = 1;   //�p���I�]�b��1��
		remainder = numerator;
		remainder.fract.numerator.append(denominator.length() - numerator.length(), '0');
		quotient.append(denominator.length() - 1, '0');
	}
	else {
		remainder = numerator.substr(0, denominator.length());
		dot = numerator.length() - denominator.length() + 1;   //�p���I��m
	}
	int i;
	for(i = 0; i <= 100 - denominator.length() + numerator.length(); i++){
		int n = 1;
		while (products[n] <= remainder)
			n++;
		n--;
		quotient.append(to_string(n));
		remainder = remainder - products[n];

		if (remainder.fract.numerator == "0" && pos >= numerator.length())   //�����F
			break;

		if (remainder.fract.numerator[0] == '0')   //�M�}�Y��0
			remainder.fract.numerator.erase(0, 1);

		pos++;
		if (pos < numerator.length())
			remainder.fract.numerator.append(string(1, numerator[pos]));
		else
			remainder.fract.numerator.append("0");
	}
	quotient.insert(dot, ".");
	while (quotient[0] == '0' && quotient[1] != '.')   //�M�}�Y��0
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
	positive = fract.numerator[0] == '-' ? false : true;   //�O�_�O�t��
	fract.numerator = positive ? fract.numerator : fract.numerator.substr(1);   //�h���t��
	int place = countDecimalPlace(str);   //��p���I����m
	if (place != -1) {   //�p�G�����p���I
		dec = true;
		string noDot = fract.numerator;
		string::iterator it = find(noDot.begin(), noDot.end(), '.');
		noDot.erase(it);   //�h���p���I
		fract.numerator = noDot;   //���l�]���h���p���I����
		fract.denominator = "1";   //�������]��1
		fract.denominator.append(place, '0');   //�����᭱�[�W0
		toIrreducible(fract);
	}
	else {   //�p�G�O���
		dec = false;
		fract.denominator = "1";
	}
}

Decimal::Decimal(const char* str) : NumberObject()
{
	if (isPureNum(str)) {   //�O���O�@�Ӽ� �٬O�⦡
		dec = true;
		fract.numerator = str;
		positive = fract.numerator[0] == '-' ? false : true;   //�O�_�O�t��
		fract.numerator = positive ? fract.numerator : fract.numerator.substr(1);   //�h���t��
		int place = countDecimalPlace(str);   //��p���I����m
		if (place != -1) {   //�p�G�����p���I
			string noDot = fract.numerator;
			string::iterator it = find(noDot.begin(), noDot.end(), '.');
			noDot.erase(it);   //�h���p���I
			fract.numerator = noDot;   //���l�]���h���p���I����
			fract.denominator = "1";   //�������]��1
			fract.denominator.append(place, '0');   //�����᭱�[�W0
			toIrreducible(fract);
		}
		else {   //�p�G�O���
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
	Integer d1(fract.denominator);   //����1
	Integer n1(fract.numerator);   //���l1
	Integer d2(num.fract.denominator);   //����2
	Integer n2(num.fract.numerator);   //���l2
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
	Integer n1(fract.numerator);   //���l1
	Integer n2(num.fract.numerator);   //���l2
	Decimal result;
	if (this->dec == false && num.dec == false) {   //�p�G�O��Ӿ�Ƭ۰�
		result = (n1 / n2).fract.numerator;
		if (!this->positive != !num.positive)
			result.positive = false;
		result.fract.denominator = "1";
		return result;
	}
	Integer d1(fract.denominator);   //����1
	Integer d2(num.fract.denominator);   //����2
	result.fract.numerator = (n1 * d2).tostring();
	result.fract.denominator = (d1 * n2).tostring();
	if (!this->positive != !num.positive)
		result.positive = false;
	toIrreducible(result.fract);
	return result;
}

const Decimal Decimal::operator+(const Decimal& num) const
{
	Integer d1(fract.denominator);   //����1
	Integer n1(fract.numerator);   //���l1
	Integer d2(num.fract.denominator);   //����2
	Integer n2(num.fract.numerator);   //���l2
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
	n1 = n1 * d2 / g;   //�q���᪺���l1
	n2 = n2 * d1 / g;   //�q���᪺���l2
	d1 = d1 * d2 / g;   //�q���᪺����
	r = n1 + n2;
	result.fract.denominator = d1.tostring();
	result.fract.numerator = r.fract.numerator;
	result.positive = r.positive;
	toIrreducible(result.fract);
	return result;
}

const Decimal Decimal::operator-(const Decimal& num) const
{
	Integer d1(fract.denominator);   //����1
	Integer n1(fract.numerator);   //���l1
	Integer d2(num.fract.denominator);   //����2
	Integer n2(num.fract.numerator);   //���l2
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
	n1 = n1 * d2 / g;   //�q���᪺���l1
	n2 = n2 * d1 / g;   //�q���᪺���l2
	d1 = d1 * d2 / g;   //�q���᪺����
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
