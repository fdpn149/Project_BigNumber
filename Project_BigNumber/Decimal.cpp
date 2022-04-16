#include "Decimal.h"

void Decimal::calculate(string str)
{

}

Decimal::Decimal(string str)
{
	calculate(str);
}

ostream& operator<<(ostream& outputStream, Decimal& numObj)
{
	cout << numObj.value;
	return outputStream;
}
