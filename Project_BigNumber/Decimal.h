#include <iostream>
using namespace std;

class Decimal : NumberObject
{
	string numerator;
	string denominator;
	string calculate(string str);
public:
	Decimal();
	Decimal(const string str);
	Decimal(const char* str);
	const string operator!() const;   //階乘
	const string operator^(const Decimal& num) const;   //次方
	const string operator*(const Decimal& num) const;   //乘
	const string operator/(const Decimal& num) const;   //除
	const string operator+(const Decimal& num) const;   //加
	const string operator-(const Decimal& num) const;   //減
	friend istream& operator>>(istream& inputStream, Decimal& numObj);
	friend ostream& operator<<(ostream& outputStream, Decimal& numObj);
};

