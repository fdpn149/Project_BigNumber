#include <iostream>
using namespace std;
class Decimal
{
	string numerator;
	string denominator;
	string value;
	void calculate(string str);
public:
	Decimal(string str);
	friend istream& operator>>(istream& inputStream, Decimal& numObj);
	friend ostream& operator<<(ostream& outputStream, Decimal& numObj);
};

