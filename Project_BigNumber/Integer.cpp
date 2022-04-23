#include "NumberObject.h"
#include "Integer.h"

string Integer::calculate(string input)
{
	stringstream ss(input);
	string now_str;
	vector<char> symbol;   //�s�Ÿ�
	vector<string> number;   //�s�Ʀr
	while (ss >> now_str) {
		if (now_str[0] == '(') {   //�A��
			int ss_loc = ss.tellg();   //ss�{�b���쪺��m
			int len = find_rparenthesis(input.substr(ss_loc - 1));   //��A���ҬA������
			string result = calculate(input.substr(ss_loc + 1, len));   //�A�������B�⵲�G
			number.push_back(result);   //�s�Ʀr
			input.replace(ss_loc - 1, len + 4, result);   //�N�A�����������G
			ss.str(input);   //���ss����
			ss.seekg(ss_loc + result.length()-1);   //�Nss������m�]�^��
		}
		else if (now_str[0] == '+' && now_str[1] == '(') {   //�� �A��
			int ss_loc = ss.tellg();
			int len = find_rparenthesis(input.substr(ss_loc + 1));   //��A���ҬA������
			string result = calculate(input.substr(ss_loc + 1, len + 2));
			number.push_back(result);   //�s�Ʀr
			input.replace(ss_loc - 2, len + 7, result);   //�N�A�����������G
			ss.str(input);   //���ss����
			ss.seekg(ss_loc + result.length()-1);   //�Nss������m�]�^��
		}
		else if (now_str[0] == '-' && now_str[1] == '(') {   //�t �A��
			int ss_loc = ss.tellg();
			int len = find_rparenthesis(input.substr(ss_loc + 1));   //��A���ҬA������
			string result = '-' + calculate(input.substr(ss_loc + 1, len + 2));
			number.push_back(result);   //�s�Ʀr
			input.replace(ss_loc - 2, len + 7, result);   //�N�A�����������G
			ss.str(input);   //���ss����
			ss.seekg(ss_loc + result.length()-1);   //�Nss������m�]�^��
		}
		else if (isalpha(now_str[0])) {   //�ܼ�

		}
		else if (isdigit(now_str[0])) {   //���
			number.push_back(now_str);
		}
		else if ((now_str[0] == '+' || now_str[0] == '-') && now_str.length() > 1) {   //���t��
			number.push_back(now_str);
		}
		else {   //�Ÿ�
			symbol.push_back(now_str[0]);
		}
	}
	return split_calculate(number, symbol);
}

string Integer::split_calculate(vector<string> &number, vector<char> &symbol)
{
	//�@��t�����B�z
	for (int i = 0; i < number.size(); i++){
		int count = 0;
		for (int j = 0; j < number[i].size(); j++){
			if (number[i][j] == '-')
				count++;
			else
				break;
		}
		if (count % 2 == 0){
			for (int j = 0; j < count; j++)
				number[i].erase(number[i].begin());
		}
		else{
			for (int j = 0; j < count - 1; j++)
				number[i].erase(number[i].begin());
		}
	}

	//�����p��
	for (int i = 0; i < symbol.size(); i++) {
		if (symbol[i] == '!') {   //�Y�J�춥��
			Integer num = number[i];
			number[i] = (!num).tostring();
			symbol.erase(symbol.begin() + i);
			i--;
		}
	}

	//����B��
	for (int i = symbol.size() - 1; i >= 0; i--) {
		if (symbol[i] == '^') {   //�Y�J�즸��
			Integer num1 = number[i];
			Integer num2 = number[i + 1];
			number[i] = (num1 ^ num2).tostring();
			number.erase(number.begin() + i + 1);
			symbol.erase(symbol.begin() + i);
		}
	}

	for (int i = 0; i < symbol.size(); i++) {
		if (symbol[i] == '*') {   //�Y�J�쭼
			Integer num1 = number[i];
			Integer num2 = number[i + 1];
			number[i] = (num1 * num2).tostring();
			number.erase(number.begin() + i + 1);
			symbol.erase(symbol.begin() + i);
			i--;
			continue;
		}
		if (symbol[i] == '/') {   //�Y�J�찣
			Integer num1 = number[i];
			Integer num2 = number[i + 1];
			number[i] = (num1 / num2).tostring();
			number.erase(number.begin() + i + 1);
			symbol.erase(symbol.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < symbol.size(); i++) {
		if (symbol[i] == '+') {   //�Y�J��[
			Integer num1 = number[i];
			Integer num2 = number[i + 1];
			number[i] = (num1 + num2).tostring();
			number.erase(number.begin() + i + 1);
			symbol.erase(symbol.begin() + i);
			i--;
			continue;
		}
		if (symbol[i] == '-') {   //�Y�J���
			Integer num1 = number[i];
			Integer num2 = number[i + 1];
			number[i] = (num1 - num2).tostring();
			number.erase(number.begin() + i + 1);
			symbol.erase(symbol.begin() + i);
			i--;
		}
	}
	return number[0];
}

bool Integer::isAllDigit(string input)
{
	for (int i = input[0] == '-' ? 1 : 0; i < input.length(); i++) {
		if (!isdigit(input[i]))
			return false;
	}
	return true;
}

Integer::Integer() : NumberObject()
{
	dec = false;
}

Integer::Integer(const string str) : NumberObject(str)
{
	positive = fract.numerator[0] == '-' ? false : true;   //�O�_�O�t��
	fract.numerator = positive ? fract.numerator : fract.numerator.substr(1);   //�h���t��
	dec = false;
}

Integer::Integer(const char* str) : NumberObject()
{
	if (isAllDigit(str))
		fract.numerator = str;
	else
		fract.numerator = calculate(str);

	positive = fract.numerator[0] == '-' ? false : true;   //�O�_�O�t��
	fract.numerator = positive ? fract.numerator : fract.numerator.substr(1);   //�h���t��
	dec = false;
}

Integer::Integer(const Integer& cp)
{
	this->fract = cp.fract;
	this->positive = cp.positive;
}

const Integer Integer::operator!() const
{
	return "9191";
}

const Integer Integer::operator^(const Integer& num) const
{
	return "7474";
}

const Integer Integer::operator%(const Integer& num) const
{
	string as = this->tostring();
	string bs = num.tostring();
	if (as.length() < bs.length())
		as.insert(as.begin(), bs.length() - as.length(), '0');   //��0
	if (as.length() > bs.length())
		bs.insert(bs.begin(), as.length() - bs.length(), '0');   //��0
	if (bs > as)
		return *this;

	Integer a = *this / num;
	return *this - (num * a);
}

const Integer Integer::operator*(const Integer& num) const
{
	map<int, Integer> products;
	products[0] = Integer();
	products[1] = *this;
	products[2] = products[1] + products[1];
	products[3] = products[1] + products[2];
	products[4] = products[2] + products[2];
	products[5] = products[2] + products[3];
	products[6] = products[3] + products[3];
	products[7] = products[3] + products[4];
	products[8] = products[4] + products[4];
	products[9] = products[4] + products[5];
	Integer sum;
	int digit = 0;
	for (int i = num.fract.numerator.length() - 1; i >= 0; i--) {
		Integer b = products[num.fract.numerator.at(i) - '0'];
		b.fract.numerator.append(digit, '0');
		sum = sum + b;
		digit++;
	}

	sum.positive = true;
	if(!positive == !num.positive)
		return sum;
	
	sum.positive = false;
	return sum;
}

const Integer Integer::operator/(const Integer& num) const
{
	if (num.fract.numerator == "0") {
		cout << "���Ƥ��ର";
		return "0";
	}
	
	map<int, Integer> products;
	products[1] = num;
	products[2] = products[1] + products[1];
	products[3] = products[1] + products[2];
	products[4] = products[2] + products[2];
	products[5] = products[2] + products[3];
	products[6] = products[3] + products[3];
	products[7] = products[3] + products[4];
	products[8] = products[4] + products[4];
	products[9] = products[4] + products[5];
	products[10] = products[5] + products[5];

	Integer a;
	string originNum = fract.numerator;
	string lastNum;
	string nowNum = originNum.substr(0, num.fract.numerator.length()-1);
	string quotient = "0";
	string compare;
	for (int i = 0; i <= (int)fract.numerator.length() - (int)num.fract.numerator.length(); i++) {
		nowNum.append(to_string(originNum[num.fract.numerator.size() + i-1] - '0'));
		int j = 1;
		lastNum = "0";
		compare = products[j].fract.numerator;
		if (compare.length() < nowNum.length())
			compare.insert(0, 1, '0');
		while (compare.length() == nowNum.length() && compare <= nowNum) {
			lastNum = compare;
			j++;
			compare = products[j].fract.numerator;
			if (compare.length() < nowNum.length())
				compare.insert(0, 1, '0');
		}
		a = Integer(nowNum) - lastNum;
		j--;
		quotient.append(to_string(j));
		nowNum = a.fract.numerator;
	}
	while(quotient.length() > 1 && quotient[0] == '0')
		quotient.erase(quotient.begin());

	a.fract.numerator = quotient;
	a.positive = true;
	if (!positive == !num.positive)
		return a;

	a.positive = false;
	return a;
}

const Integer Integer::operator+(const Integer& num) const
{
	Integer numA, numB;
	numA = *this;
	numB = num;

	if (!this->positive == !num.positive) {   //�P��
		if (numA.getNumeratorSize() < numB.getNumeratorSize())
			numA.fract.numerator.insert(numA.fract.numerator.begin(), numB.getNumeratorSize() - numA.getNumeratorSize(), '0');   //��0
		else if(numA.getNumeratorSize() > numB.getNumeratorSize())
			numB.fract.numerator.insert(numB.fract.numerator.begin(), numA.getNumeratorSize() - numB.getNumeratorSize(), '0');   //��0
		bool over = false;   //�i��
		for (int i = numA.getNumeratorSize() - 1; i >= 0; i--) {
			numA.fract.numerator[i] += numB.fract.numerator[i] + over - 48;
			over = false;
			if (numA.fract.numerator[i] > '9') {
				over = 1;
				numA.fract.numerator[i] -= 10;
			}
		}
		if (over)
			numA.fract.numerator.insert(numA.fract.numerator.begin(), '1');

		return numA;
	}
	else if (positive) {   //A+(-B)
		numB.positive = true;
		return numA - numB;
	}
	else {   //(-A)+B
		numA.positive = true;
		return numB - numA;
	}
}

const Integer Integer::operator-(const Integer& num) const
{
	Integer numA, numB;
	numA = *this;
	numB = num;

	if (!this->positive == !num.positive) {   //�P��
		if (!positive)   //(-A)-(-B)
			numA.fract.numerator.swap(numB.fract.numerator);   //�令B-A

		if (numA.getNumeratorSize() < numB.getNumeratorSize())
			numA.fract.numerator.insert(numA.fract.numerator.begin(), numB.getNumeratorSize() - numA.getNumeratorSize(), '0');   //��0
		else if (numA.getNumeratorSize() > numB.getNumeratorSize())
			numB.fract.numerator.insert(numB.fract.numerator.begin(), numA.getNumeratorSize() - numB.getNumeratorSize(), '0');   //��0
		bool inverse;
		if (numA.fract.numerator < numB.fract.numerator) {   //A < B
			inverse = 1;
			numA.fract.numerator.swap(numB.fract.numerator);
		}
		else   //A > B
			inverse = false;

		for (int i = 0; i < numA.getNumeratorSize(); i++) {
			numA.fract.numerator[i] -= numB.fract.numerator[i] - '0';
			if (numA.fract.numerator[i] < '0') {
				for (int j = i; j >= 1; j--) {
					numA.fract.numerator[j] += 10;
					numA.fract.numerator[j - 1] -= 1;
					if (numA.fract.numerator[j - 1] >= '0')
						break;
				}
			}
		}

		for (int i = 0; i < numA.getNumeratorSize(); i++) {
			if (numA.fract.numerator[i] == '0') {
				numA.fract.numerator.erase(numA.fract.numerator.begin() + i);
				i--;
			}
			else
				break;
		}

		if (numA.getNumeratorSize() == 0)
			numA = "0";

		if (inverse)
			numA.positive = false;
		else
			numA.positive = true;

			return numA;
	}
	else if (positive) {   //A-(-B)
		return numA + numB;
	}
	else {   //(-A)-B
		numA.positive = true;
		numA = numA + numB;
		numA.positive = false;
		return numA;
	}
}

void Integer::operator=(const Integer& num)
{
	this->fract = num.fract;
	this->positive = num.positive;
}

const bool Integer::operator==(const Integer& num) const
{
	return this->fract.numerator == num.fract.numerator;
}

const bool Integer::operator>(const Integer& num) const
{
	if (this->getNumeratorSize() > num.getNumeratorSize())
		return 1;
	else if (this->getNumeratorSize() < num.getNumeratorSize())
		return 0;
	else
		return this->fract.numerator > num.fract.numerator;
}

const bool Integer::operator<(const Integer& num) const
{
	if (this->getNumeratorSize() < num.getNumeratorSize())
		return 1;
	else if (this->getNumeratorSize() > num.getNumeratorSize())
		return 0;
	else
		return this->fract.numerator < num.fract.numerator;
}

const bool Integer::operator<=(const Integer& num) const
{
	if (this->getNumeratorSize() < num.getNumeratorSize())
		return 1;
	else if (this->getNumeratorSize() > num.getNumeratorSize())
		return 0;
	else
		return this->fract.numerator <= num.fract.numerator;
}

const string Integer::tostring() const
{
	if (positive)
		return fract.numerator;
	else
		return '-' + fract.numerator;
}

ostream& operator<<(ostream& outputStream, Integer& numObj)
{
	cout << (numObj.positive ? numObj.fract.numerator : "-" + numObj.fract.numerator);
	return outputStream;
}
