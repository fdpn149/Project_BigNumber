#include <iostream>
using namespace std;
class Integer
{
	string value;
	void process(string str);
public:
	Integer(string str);
	friend istream& operator>>(istream& inputStream, Integer& numObj);
	friend ostream& operator<<(ostream& outputStream, Integer& numObj);
};

