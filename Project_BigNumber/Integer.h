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
	const string operator!() const;   //����
	const string operator^(const Integer& num) const;   //����
	const string operator*(const Integer& num) const;   //��
	const string operator/(const Integer& num) const;   //��
	const string operator+(const Integer& num) const;   //�[
	const string operator-(const Integer& num) const;   //��
	friend istream& operator>>(istream& inputStream, Integer& numObj);
	friend ostream& operator<<(ostream& outputStream, Integer& numObj);
};

