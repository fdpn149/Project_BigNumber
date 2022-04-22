#pragma once
#include "NumberObject.h"
#include "Integer.h"

class Decimal : public NumberObject
{
	fraction calculate(string str);
	fraction split_calculate(vector<fraction>& number, vector<char>& symbol);
	bool isPureNum(string input);
	int countDecimalPlace(string str);
	void toIrreducible(fraction& f);
	Integer gcd(Integer a, Integer b);
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