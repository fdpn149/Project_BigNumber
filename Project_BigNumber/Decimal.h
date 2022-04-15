#include <iostream>
using namespace std;
class Decimal
{
	int numerator;
	int denominator;
public:
	friend istream& operator>>(istream& inputStream, Decimal& numObj);
	friend ostream& operator<<(ostream& outputStream, Decimal& numObj);
};

