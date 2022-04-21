#include "NumberObject.h"
#include "Decimal.h"

string Decimal::calculate(string str)
{
	return string();
}

Decimal::Decimal() : NumberObject()
{
	string zero = "0.";
	zero.append(100, '0');
	value = zero;
}

Decimal::Decimal(const string str) : NumberObject(str)
{
	positive = value[0] == '-' ? false : true;   //是否是負數
	value = positive ? value : value.substr(1);   //去掉負號
}

Decimal::Decimal(const char* str) : NumberObject()
{
	if (isAllDigit(str))
		value = str;
	else
		value = calculate(str);

	positive = value[0] == '-' ? false : true;   //是否是負數
	value = positive ? value : value.substr(1);   //去掉負號
}

const string Decimal::operator!() const
{
	return string();
}

const string Decimal::operator^(const Decimal& num) const
{
	return string();
}

const string Decimal::operator*(const Decimal& num) const
{
	return string();
}

const string Decimal::operator/(const Decimal& num) const
{
	return string();
}

const string Decimal::operator+(const Decimal& num) const
{
	return string();
}

const string Decimal::operator-(const Decimal& num) const
{
	return string();
}

ostream& operator<<(ostream& outputStream, Decimal& numObj)
{
	cout << numObj.value;
	return outputStream;
}
