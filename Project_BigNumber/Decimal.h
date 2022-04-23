#pragma once
#include "NumberObject.h"
#include "Integer.h"

class Decimal : public NumberObject
{
	Decimal calculate(string input);   //�B�z�p��
	Decimal split_calculate(vector<Decimal>& number, vector<char>& symbol);   //��}�p��
	bool isPureNum(string input);   //�O�_�O�¼ƭ�
	int countDecimalPlace(string str);   //�p��p�Ʀ��X��
	void toIrreducible(fraction& f) const;   //�Ʀ���²����
	const Integer gcd(Integer a, Integer b) const;   //�̤j���]��
	const string findExactlyValue();   //�N�����ন�p��
	void sqrt(Decimal& d) const;
public:
	Decimal();
	Decimal(const string str);
	Decimal(const char* str);
	const Decimal operator!() const;   //����
	const Decimal operator^(const Decimal& num) const;   //����
	const Decimal operator*(const Decimal& num) const;   //��
	const Decimal operator/(const Decimal& num) const;   //��
	const Decimal operator+(const Decimal& num) const;   //�[
	const Decimal operator-(const Decimal& num) const;   //��
	friend istream& operator>>(istream& inputStream, Decimal& numObj);
	friend ostream& operator<<(ostream& outputStream, Decimal& numObj);
};