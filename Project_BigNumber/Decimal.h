#pragma once
#include "NumberObject.h"
#include "Integer.h"

class Decimal : public NumberObject
{
	Decimal calculate(string input);   //矪瞶璸衡
	Decimal split_calculate(vector<Decimal>& number, vector<char>& symbol);   //╊秨璸衡
	bool isPureNum(string input);   //琌琌计
	int countDecimalPlace(string str);   //璸衡计Τ碭
	void toIrreducible(fraction& f) const;   //てΘ程虏だ计
	const Integer gcd(Integer a, Integer b) const;   //程そ计
	const string findExactlyValue();   //盢だ计锣Θ计
	void sqrt(Decimal& d) const;
public:
	Decimal();
	Decimal(const string str);
	Decimal(const char* str);
	const Decimal operator!() const;   //顶
	const Decimal operator^(const Decimal& num) const;   //Ωよ
	const Decimal operator*(const Decimal& num) const;   //
	const Decimal operator/(const Decimal& num) const;   //埃
	const Decimal operator+(const Decimal& num) const;   //
	const Decimal operator-(const Decimal& num) const;   //搭
	friend istream& operator>>(istream& inputStream, Decimal& numObj);
	friend ostream& operator<<(ostream& outputStream, Decimal& numObj);
};