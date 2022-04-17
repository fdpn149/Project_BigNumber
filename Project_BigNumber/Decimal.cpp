#include "Decimal.h"

void Decimal::calculate(string str)
{

}

Decimal::Decimal(const string str)
{
	calculate(str);
}

Decimal::Decimal(const char* str)
{

}

ostream& operator<<(ostream& outputStream, Decimal& numObj)
{
	cout << numObj.value;
	return outputStream;
}
