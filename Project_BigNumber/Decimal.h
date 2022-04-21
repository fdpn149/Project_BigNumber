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
	const string operator!() const;   //����
	const string operator^(const Decimal& num) const;   //����
	const string operator*(const Decimal& num) const;   //��
	const string operator/(const Decimal& num) const;   //��
	const string operator+(const Decimal& num) const;   //�[
	const string operator-(const Decimal& num) const;   //��
	friend istream& operator>>(istream& inputStream, Decimal& numObj);
	friend ostream& operator<<(ostream& outputStream, Decimal& numObj);
};

