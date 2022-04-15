#include <iostream>
#include <string>
#include <cctype>
#include <sstream>
#include <vector>
#include "Decimal.h"
#include "Integer.h"
using namespace std;

struct Variable {
	string name;
	string type;
	string value;
};

vector<Variable> variable = { {"abc", "Decimal", "3.14"}, {"defg","Integer","98"}, {"hij", "Decimal", "3.14"} };

bool findExistVariable(string input)
{
	stringstream ss(input);
	string str;
	while (ss >> str) {
		if (isalpha(str[0])) {
			bool exist = false;
			for (Variable v : variable) {
				if (v.name == str) {
					exist = true;
					break;
				}
			}
			if (!exist)
				return false;
		}
	}
	return true;
}

bool isDecimal(string input)
{
	if (find(input.begin(), input.end(), '.') != input.end()) {   //�p��
		return true;
	}
	else {
		stringstream ss(input);
		string str;
		while (ss >> str) {
			if (isalpha(str[0])) {
				for (int i = 0; i < variable.size(); i++) {
					if (str == variable[i].name) {
						if (variable[i].type == "Decimal")   //�p��
							return true;
					}
				}
			}
		}
		return false;   //���
	}
}



int main()
{
	char firstChar;
	string input;

	while (firstChar = cin.peek()) {
		getline(cin, input);
		if (firstChar == 'S') {   //�i��O�ܼƩ�Set
			stringstream ss(input);
			string str;
			ss >> str;
			if (str == "Set") {   //�]�w
				cout << "�]�w" << endl;
			}
			else {   //�ܼ�
				if (findExistVariable(input)) {
					if (isDecimal(input)) {
						cout << "�p��" << endl;
						Decimal decimal = input;
						cout << decimal;
					}
					else {
						cout << "���" << endl;
						Integer integer = input;
						cout << integer;
					}
				}
				else {
					cout << "�䤣���ܼ�" << endl;
				}
			}
		}
		else {
			if (findExistVariable(input)) {
				if (isDecimal(input)) {
					cout << "�p��" << endl;
					Decimal decimal = input;
					cout << decimal;
				}
				else {
					cout << "���" << endl;
					Integer integer = input;
					cout << integer;
				}
			}
			else {
				cout << "�䤣���ܼ�" << endl;
			}
		}



		//	if (firstChar >= '0' && firstChar <= '9') {   //�Ʀr
		//		cout << "�Ʀr" << endl;
		//		getline(cin, input);
		//		if (findExistVariable(input)) {
		//			cout << "���ܼ�" << endl;
		//			if (isDecimal(input))
		//				cout << "�p��" << endl;
		//			else
		//				cout << "���" << endl;
		//		}
		//		else {
		//			cout << "�䤣���ܼ�" << endl;
		//		}
		//	}
		//	else if (firstChar == '(') {   //�A��
		//		cout << "�A��" << endl;
		//		getline(cin, input);
		//		if (findExistVariable(input)) {
		//			cout << "���ܼ�" << endl;
		//			if (isDecimal(input))
		//				cout << "�p��" << endl;
		//			else
		//				cout << "���" << endl;
		//		}
		//		else {
		//			cout << "�䤣���ܼ�" << endl;
		//		}
		//	}
		//	else if (firstChar == '-') {   //�t��
		//		cout << "�t��" << endl;
		//		getline(cin, input);
		//		if (findExistVariable(input)) {
		//			cout << "���ܼ�" << endl;
		//			if (isDecimal(input))
		//				cout << "�p��" << endl;
		//			else
		//				cout << "���" << endl;
		//		}
		//		else {
		//			cout << "�䤣���ܼ�" << endl;
		//		}
		//	}
		//	else if (firstChar == 'S') {   //�i��O�ܼƩ�Set
		//		getline(cin, input);
		//		stringstream ss(input);
		//		string str;
		//		ss >> str;
		//		if (str == "Set") {   //�]�w
		//			cout << "�]�w" << endl;
		//		}
		//		else {   //�ܼ�
		//			if (findExistVariable(input)) {
		//				cout << "���ܼ�" << endl;
		//				if (isDecimal(input))
		//					cout << "�p��" << endl;
		//				else
		//					cout << "���" << endl;
		//			}
		//			else {
		//				cout << "�䤣���ܼ�" << endl;
		//			}
		//		}
		//	}
		//	else if (isalpha(firstChar)) {   //�ܼ�
		//		getline(cin, input);
		//		if (findExistVariable(input)) {
		//			cout << "���ܼ�" << endl;
		//			if (isDecimal(input))
		//				cout << "�p��" << endl;
		//			else
		//				cout << "���" << endl;
		//		}
		//		else {
		//			cout << "�䤣���ܼ�" << endl;
		//		}
		//		
		//	}
		//	else {   //�U��
		//		cout << "�U��" << endl;
		//		getline(cin, input);
		//	}
	}
}

