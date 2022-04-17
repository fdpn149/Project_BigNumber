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
	string a = "9876543210123456789";
	string b = "0123456789876543210";
	Integer A = a;
	Integer B = b;
	cout << A << endl << B << endl;
	cout << A - B;
	//char firstChar;
	//string input;

	//while (firstChar = cin.peek()) {
	//	getline(cin, input);
	//	if (firstChar == 'S') {   //琌跑计┪Set
	//		stringstream ss(input);
	//		string str;
	//		ss >> str;
	//		if (str == "Set") {   //砞﹚
	//			cout << "砞﹚" << endl;
	//		}
	//		else {   //跑计
	//			if (areExistedVariable(input)) {
	//				if (isDecimal(input)) {
	//					cout << "计" << endl;
	//					Decimal decimal = input;
	//					//cout << decimal;
	//				}
	//				else {
	//					cout << "俱计" << endl;
	//					Integer integer = input.c_str();
	//					//cout << integer;
	//				}
	//			}
	//			else {
	//				cout << "тぃ跑计" << endl;
	//			}
	//		}
	//	}
	//	else if (firstChar != string::npos) {
	//		if (areExistedVariable(input)) {
	//			if (isDecimal(input)) {
	//				cout << "计" << endl;
	//				Decimal decimal = input;
	//				//cout << decimal;
	//			}
	//			else {
	//				cout << "俱计" << endl;
	//				Integer integer = input.c_str();
	//				//cout << integer;
	//			}
	//		}
	//		else {
	//			cout << "тぃ跑计" << endl;
	//		}
	//	}
	//	else
	//		break;
	//}
}

