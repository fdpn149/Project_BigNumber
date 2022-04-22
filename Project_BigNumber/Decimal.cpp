#include "NumberObject.h"
#include "Decimal.h"
#include "Integer.h"

fraction Decimal::calculate(string str)
{
	return fraction();
}

fraction Decimal::split_calculate(vector<fraction>& number, vector<char>& symbol)
{
	return fraction();
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

void Decimal::toIrreducible(fraction& f)
{
	if (f.denominator == "1")
		return;
	Integer a = f.numerator;
	Integer b = f.denominator;
	Integer g = gcd(a, b);
	a = a / g;
	b = b / g;
	f.numerator = a.fract.numerator;
	f.denominator = b.fract.numerator;
}

Integer Decimal::gcd(Integer a, Integer b)
{
	Integer c;
	while (b.fract.numerator != "0") {
		c = a % b;
		a = b;
		b = c;
	}
	return a;
}

Decimal::Decimal() : NumberObject()
{
	fract.numerator = "0";
	fract.denominator = "1";
}

Decimal::Decimal(const string str) : NumberObject()
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
			fract.denominator = "1";
		}
	}
	else
		fract = calculate(str);
}

Decimal::Decimal(const char* str) : NumberObject()
{
	if (isPureNum(str)) {   //�O���O�@�Ӽ� �٬O�⦡
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
			fract.numerator.append(100 - place, '0');   //�Ʀr���ڸ�0
			toIrreducible(fract);
		}
		else {   //�p�G�O���
			fract.numerator = fract.numerator;
			fract.denominator = "1";
			fract.numerator.append(".");   //�ɤW�p���I
			fract.numerator.append(100, '0');   //�ɤW�p���I�᪺100��0
		}
	}
	else
		fract = calculate(str);
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
	return Decimal();
}

const Decimal Decimal::operator/(const Decimal& num) const
{
	return Decimal();
}

const Decimal Decimal::operator+(const Decimal& num) const
{
	return Decimal();
}

const Decimal Decimal::operator-(const Decimal& num) const
{
	return Decimal();
}

ostream& operator<<(ostream& outputStream, Decimal& numObj)
{
	cout << numObj.fract.numerator << "/" << numObj.fract.denominator;
	return outputStream;
}
