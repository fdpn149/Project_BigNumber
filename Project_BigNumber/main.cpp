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

bool areExistedVariable(string input)
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
				if (areExistedVariable(input)) {
					if (isDecimal(input)) {
						//cout << "�p��" << endl;
						Decimal decimal = input;
						cout << decimal << endl;
					}
					else {
						//cout << "���" << endl;
						Integer integer = input.c_str();
						cout << integer << endl;
					}
				}
				else {
					cout << "�䤣���ܼ�" << endl;
				}
			}
		}
		else if (firstChar != string::npos) {
			if (areExistedVariable(input)) {
				if (isDecimal(input)) {
					//cout << "�p��" << endl;
					Decimal decimal = input;
					cout << decimal << endl;
				}
				else {
					//cout << "���" << endl;
					Integer integer = input.c_str();
					cout << integer << endl;
				}
			}
			else {
				cout << "�䤣���ܼ�" << endl;
			}
		}
		else
			break;
	}
}

