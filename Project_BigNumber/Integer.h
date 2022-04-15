#include <iostream>
using namespace std;
class Integer
{
	string value;
	void calculate(string str);
public:
	Integer(string str);
	friend istream& operator>>(istream& inputStream, Integer& numObj);
	friend ostream& operator<<(ostream& outputStream, Integer& numObj);
};

