#include <iostream>
using namespace std;
class Integer
{
public:
	friend istream& operator>>(istream& inputStream, Integer& numObj);
	friend ostream& operator<<(ostream& outputStream, Integer& numObj);
};

