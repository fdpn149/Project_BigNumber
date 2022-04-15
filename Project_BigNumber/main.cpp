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
	if (find(input.begin(), input.end(), '.') != input.end()) {   //计
		return true;
	}
	else {
		stringstream ss(input);
		string str;
		while (ss >> str) {
			if (isalpha(str[0])) {
				for (int i = 0; i < variable.size(); i++) {
					if (str == variable[i].name) {
						if (variable[i].type == "Decimal")   //计
							return true;
					}
				}
			}
		}
		return false;   //俱计
	}
}



int main()
{
	char firstChar;
	string input;

	while (firstChar = cin.peek()) {
		getline(cin, input);
		if (firstChar == 'S') {   //琌跑计┪Set
			stringstream ss(input);
			string str;
			ss >> str;
			if (str == "Set") {   //砞﹚
				cout << "砞﹚" << endl;
			}
			else {   //跑计
				if (findExistVariable(input)) {
					if (isDecimal(input)) {
						cout << "计" << endl;
						Decimal decimal = input;
						cout << decimal;
					}
					else {
						cout << "俱计" << endl;
						Integer integer = input;
						cout << integer;
					}
				}
				else {
					cout << "тぃ跑计" << endl;
				}
			}
		}
		else {
			if (findExistVariable(input)) {
				if (isDecimal(input)) {
					cout << "计" << endl;
					Decimal decimal = input;
					cout << decimal;
				}
				else {
					cout << "俱计" << endl;
					Integer integer = input;
					cout << integer;
				}
			}
			else {
				cout << "тぃ跑计" << endl;
			}
		}



		//	if (firstChar >= '0' && firstChar <= '9') {   //计
		//		cout << "计" << endl;
		//		getline(cin, input);
		//		if (findExistVariable(input)) {
		//			cout << "Τ跑计" << endl;
		//			if (isDecimal(input))
		//				cout << "计" << endl;
		//			else
		//				cout << "俱计" << endl;
		//		}
		//		else {
		//			cout << "тぃ跑计" << endl;
		//		}
		//	}
		//	else if (firstChar == '(') {   //珹腹
		//		cout << "珹腹" << endl;
		//		getline(cin, input);
		//		if (findExistVariable(input)) {
		//			cout << "Τ跑计" << endl;
		//			if (isDecimal(input))
		//				cout << "计" << endl;
		//			else
		//				cout << "俱计" << endl;
		//		}
		//		else {
		//			cout << "тぃ跑计" << endl;
		//		}
		//	}
		//	else if (firstChar == '-') {   //璽腹
		//		cout << "璽腹" << endl;
		//		getline(cin, input);
		//		if (findExistVariable(input)) {
		//			cout << "Τ跑计" << endl;
		//			if (isDecimal(input))
		//				cout << "计" << endl;
		//			else
		//				cout << "俱计" << endl;
		//		}
		//		else {
		//			cout << "тぃ跑计" << endl;
		//		}
		//	}
		//	else if (firstChar == 'S') {   //琌跑计┪Set
		//		getline(cin, input);
		//		stringstream ss(input);
		//		string str;
		//		ss >> str;
		//		if (str == "Set") {   //砞﹚
		//			cout << "砞﹚" << endl;
		//		}
		//		else {   //跑计
		//			if (findExistVariable(input)) {
		//				cout << "Τ跑计" << endl;
		//				if (isDecimal(input))
		//					cout << "计" << endl;
		//				else
		//					cout << "俱计" << endl;
		//			}
		//			else {
		//				cout << "тぃ跑计" << endl;
		//			}
		//		}
		//	}
		//	else if (isalpha(firstChar)) {   //跑计
		//		getline(cin, input);
		//		if (findExistVariable(input)) {
		//			cout << "Τ跑计" << endl;
		//			if (isDecimal(input))
		//				cout << "计" << endl;
		//			else
		//				cout << "俱计" << endl;
		//		}
		//		else {
		//			cout << "тぃ跑计" << endl;
		//		}
		//		
		//	}
		//	else {   //︰В
		//		cout << "︰В" << endl;
		//		getline(cin, input);
		//	}
	}
}

