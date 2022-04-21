#include <iostream>
#include <sstream>
#include <vector>
#include <cctype>
#include <map>
using namespace std;
class Integer : public NumberObject
{
	string calculate(string input);
	string split_calculate(vector<string> &number, vector<char> &symbol);
public:
	Integer();
	Integer(const string str);
	Integer(const char* str);
	const string operator!() const;   //階乘
	const string operator^(const Integer& num) const;   //次方
	const string operator*(const Integer& num) const;   //乘
	const string operator/(const Integer& num) const;   //除
	const string operator+(const Integer& num) const;   //加
	const string operator-(const Integer& num) const;   //減
	friend istream& operator>>(istream& inputStream, Integer& numObj);
	friend ostream& operator<<(ostream& outputStream, Integer& numObj);
};

