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
	const Decimal operator!() const;   //階乘
	const Decimal operator^(const Decimal& num) const;   //次方
	const Decimal operator*(const Decimal& num) const;   //乘
	const Decimal operator/(const Decimal& num) const;   //除
	const Decimal operator+(const Decimal& num) const;   //加
	const Decimal operator-(const Decimal& num) const;   //減
	friend istream& operator>>(istream& inputStream, Decimal& numObj);
	friend ostream& operator<<(ostream& outputStream, Decimal& numObj);
};