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
	/*(�@��t�����B�z)*/

	//�����p��
	for (int i = 0; i < symbol.size(); i++) {
		if (symbol[i] == '!') {   //�Y�J�춥��
			Integer num = number[i];
			number[i] = !num;
			symbol.erase(symbol.begin() + i);
			i--;
		}
	}

	//����B��
	for (int i = 0; i < symbol.size(); i++) {
		if (symbol[i] == '^') {   //�Y�J�즸��
			Integer num1 = number[i];
			Integer num2 = number[i + 1];
			number[i] = num1 ^ num2;
			number.erase(number.begin() + i + 1);
			symbol.erase(symbol.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < symbol.size(); i++) {
		if (symbol[i] == '*') {   //�Y�J�쭼
			Integer num1 = number[i];
			Integer num2 = number[i + 1];
			number[i] = num1 * num2;
			number.erase(number.begin() + i + 1);
			symbol.erase(symbol.begin() + i);
			i--;
			continue;
		}
		if (symbol[i] == '/') {   //�Y�J�찣
			Integer num1 = number[i];
			Integer num2 = number[i + 1];
			number[i] = num1 / num2;
			number.erase(number.begin() + i + 1);
			symbol.erase(symbol.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < symbol.size(); i++) {
		if (symbol[i] == '+') {   //�Y�J��[
			Integer num1 = number[i];
			Integer num2 = number[i + 1];
			number[i] = num1 + num2;
			number.erase(number.begin() + i + 1);
			symbol.erase(symbol.begin() + i);
			i--;
			continue;
		}
		if (symbol[i] == '-') {   //�Y�J���
			Integer num1 = number[i];
			Integer num2 = number[i + 1];
			number[i] = num1 - num2;
			number.erase(number.begin() + i + 1);
			symbol.erase(symbol.begin() + i);
			i--;
		}
	}
	return number[0];
}

Integer::Integer() : NumberObject()
{
}

Integer::Integer(const string str) : NumberObject(str)
{
	positive = value[0] == '-' ? false : true;   //�O�_�O�t��
	value = positive ? value : value.substr(1);   //�h���t��
}

Integer::Integer(const char* str) : NumberObject()
{
	if (isAllDigit(str))
		value = str;
	else
		value = calculate(str);

	positive = value[0] == '-' ? false : true;   //�O�_�O�t��
	value = positive ? value : value.substr(1);   //�h���t��
}

const string Integer::operator!() const
{
	return "9191";
}

const string Integer::operator^(const Integer& num) const
{
	return "7474";
}

const string Integer::operator*(const Integer& num) const
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
	for (int i = num.value.length() - 1; i >= 0; i--) {
		Integer b = products[num.value.at(i) - '0'];
		b.value.append(digit, '0');
		sum = sum + b;
		digit++;
	}
	if(!positive == !num.positive)
		return sum.value;
	else
		return '-' + sum.value;
}

const string Integer::operator/(const Integer& num) const
{
	if (num.value == "0") {
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
	string originNum = value;
	string lastNum;
	string nowNum = originNum.substr(0, num.value.length()-1);
	string quotient = "0";
	string compare;
	for (int i = 0; i <= (int)value.length() - (int)num.value.length(); i++) {
		nowNum.append(to_string(originNum[num.value.size() + i-1] - '0'));
		int j = 1;
		lastNum = "0";
		compare = products[j].value;
		if (compare.length() < nowNum.length())
			compare.insert(0, 1, '0');
		while (compare.length() == nowNum.length() && compare <= nowNum) {
			lastNum = compare;
			j++;
			compare = products[j].value;
			if (compare.length() < nowNum.length())
				compare.insert(0, 1, '0');
		}
		a = Integer(nowNum) - lastNum;
		j--;
		quotient.append(to_string(j));
		nowNum = a.value;
	}
	while(quotient.length() > 1 && quotient[0] == '0')
		quotient.erase(quotient.begin());

	if (!positive == !num.positive)
		return quotient;
	else
		return '-' + quotient;
}

const string Integer::operator+(const Integer& num) const
{
	string numA, numB;
	numA = this->value;
	numB = num.value;

	if (!this->positive == !num.positive) {   //�P��
		if (numA.size() < numB.size())
			numA.insert(numA.begin(), numB.size() - numA.size(), '0');   //��0
		else if(numA.size() > numB.size())
			numB.insert(numB.begin(), numA.size() - numB.size(), '0');   //��0
		bool over = false;   //�i��
		for (int i = numA.size() - 1; i >= 0; i--) {
			numA[i] += numB[i] + over - 48;
			over = false;
			if (numA[i] > '9') {
				over = 1;
				numA[i] -= 10;
			}
		}
		if (over)
			numA.insert(numA.begin(), '1');
		if (!positive)
			numA.insert(numA.begin(), '-');
		return numA;
	}
	else if (positive) {   //A+(-B)
		return *this - Integer(numB);
	}
	else {   //(-A)+B
		return num - Integer(numA);
	}
}

const string Integer::operator-(const Integer& num) const
{
	string numA, numB;
	numA = this->value;
	numB = num.value;

	if (!this->positive == !num.positive) {   //�P��
		if (!positive)   //(-A)-(-B)
			numA.swap(numB);   //�令B-A
		if (numA.size() < numB.size())
			numA.insert(numA.begin(), numB.size() - numA.size(), '0');   //��0
		else if (numA.size() > numB.size())
			numB.insert(numB.begin(), numA.size() - numB.size(), '0');   //��0
		bool inverse;
		if (numA < numB) {   //A < B
			inverse = 1;
			numA.swap(numB);
		}
		else   //A > B
			inverse = false;

		for (int i = 0; i < numA.size(); i++) {
			numA[i] -= numB[i] - '0';
			if (numA[i] < '0') {
				for (int j = i; j >= 1; j--) {
					numA[j] += 10;
					numA[j - 1] -= 1;
					if (numA[j - 1] >= '0')
						break;
				}
			}
		}

		for (int i = 0; i < numA.size(); i++) {
			if (numA[i] == '0') {
				numA.erase(numA.begin() + i);
				i--;
			}
			else
				break;
		}

		if (numA.size() == 0)
			numA = "0";

		if (inverse)
			return '-' + numA;
		else
			return numA;
	}
	else if (positive) {   //A-(-B)
		return *this + Integer(numB);
	}
	else {   //(-A)-B
		return '-' + (num + Integer(numA));
	}
}

ostream& operator<<(ostream& outputStream, Integer& numObj)
{
	cout << (numObj.positive ? numObj.value : "-" + numObj.value);
	return outputStream;
}
