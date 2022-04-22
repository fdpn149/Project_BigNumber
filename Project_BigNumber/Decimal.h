#pragma once
#include "NumberObject.h"
#include "Integer.h"

class Decimal : public NumberObject
{
	Decimal calculate(string input);
	Decimal split_calculate(vector<Decimal>& number, vector<char>& symbol);
	bool isPureNum(string input);
	int countDecimalPlace(string str);
	void toIrreducible(fraction& f) const;
	const Integer gcd(Integer a, Integer b) const;
	const Integer lcm(Integer a, Integer b) const;
	const string findExactlyValue();
public:
	Decimal();
	Decimal(const string str);
	Decimal(const char* str);
	const Decimal operator!() const;   //����
	const Decimal operator^(const Decimal& num) const;   //����
	const Decimal operator*(const Decimal& num) const;   //��
	const Decimal operator/(const Decimal& num) const;   //��
	const Decimal operator+(const Decimal& num) const;   //�[
	const Decimal operator-(const Decimal& num) const;   //��
	friend istream& operator>>(istream& inputStream, Decimal& numObj);
	friend ostream& operator<<(ostream& outputStream, Decimal& numObj);
};