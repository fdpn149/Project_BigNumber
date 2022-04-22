#pragma once

class Integer : public NumberObject
{
	string calculate(string input);
	string split_calculate(vector<string> &number, vector<char> &symbol);
	bool isAllDigit(string input);
public:
	Integer();
	Integer(const string str);
	Integer(const char* str);
	const Integer operator!() const;   //階乘
	const Integer operator^(const Integer& num) const;   //次方
	const Integer operator%(const Integer& num) const;   //餘
	const Integer operator*(const Integer& num) const;   //乘
	const Integer operator/(const Integer& num) const;   //除
	const Integer operator+(const Integer& num) const;   //加
	const Integer operator-(const Integer& num) const;   //減
	void operator=(const Integer& num);
	friend istream& operator>>(istream& inputStream, Integer& numObj);
	friend ostream& operator<<(ostream& outputStream, Integer& numObj);
	const string tostring() const;
};