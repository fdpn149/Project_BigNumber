#include <iostream>
#include <sstream>
#include <vector>
#include <cctype>
using namespace std;

class Integer
{
	string value;
	int find_rparenthesis(string str);   //��k�A������m
	void process(string str);
	string calculate(string input);
public:
	Integer(string str);
	friend istream& operator>>(istream& inputStream, Integer& numObj);
	friend ostream& operator<<(ostream& outputStream, Integer& numObj);
};

