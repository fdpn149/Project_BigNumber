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
	Integer(const Integer& cp);
	const Integer operator!() const;   //����
	const Integer operator^(const Integer& num) const;   //����
	const Integer operator%(const Integer& num) const;   //�l(�����)
	const Integer operator*(const Integer& num) const;   //��
	const Integer operator/(const Integer& num) const;   //��
	const Integer operator+(const Integer& num) const;   //�[
	const Integer operator-(const Integer& num) const;   //��
	void operator=(const Integer& num);
	const bool operator==(const Integer& num) const;
	const bool operator>(const Integer& num) const;
	const bool operator>=(const Integer& num) const;
	const bool operator<(const Integer& num) const;
	const bool operator<=(const Integer& num) const;
	friend istream& operator>>(istream& inputStream, Integer& numObj);
	friend ostream& operator<<(ostream& outputStream, Integer& numObj);
	const string tostring() const;
};