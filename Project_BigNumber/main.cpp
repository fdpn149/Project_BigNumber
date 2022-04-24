#include "NumberObject.h"
#include "Decimal.h"
#include "Integer.h"

struct Variable {
	string name;
	string type;
	string value;
};

vector<Variable> variable = { {"abc", "Decimal", "3.14"}, {"defg","Integer","98"}, {"hij", "Decimal", "3.14"} };

bool areExistedVariable(string input);
bool isDecimal(string input);
void printError(int err)
{
	switch (err) {
	case -2:
		cout << "块ΑΤ粇" << endl; break;
	case -1:
		cout << "璽计ぃ秨腹" << endl; break;
	case 0:
		cout << "埃计ぃ0" << endl; break;
	case 1:
		cout << "璽计ぃ衡顶" << endl; break;
	case 2:
		cout << "计ぃ衡顶" << endl; break;
	case 3:
		cout << "计叫块0.5计" << endl; break;
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
				if (areExistedVariable(input)) {
					if (isDecimal(input)) {
						//cout << "计" << endl;
						try {
							Decimal decimal = input.c_str();
							cout << decimal << endl;
						}
						catch (int err) {
							printError(err);
						}
						catch (out_of_range) {
							printError(-2);
						}
					}
					else {
						//cout << "俱计" << endl;
						try {
							Integer integer = input.c_str();
							cout << integer << endl;
						}
						catch (int err) {
							printError(err);
						}
						catch (out_of_range) {
							printError(-2);
						}
					}
				}
				else {
					cout << "тぃ跑计" << endl;
				}
			}
		}
		else if (firstChar != string::npos) {
			if (areExistedVariable(input)) {
				if (isDecimal(input)) {
					//cout << "计" << endl;
					try {
						Decimal decimal = input.c_str();
						cout << decimal << endl;
					}
					catch (int err) {
						printError(err);
					}
					catch (out_of_range) {
						printError(-2);
					}
				}
				else {
					//cout << "俱计" << endl;
					try {
						Integer integer = input.c_str();
						cout << integer << endl;
					}
					catch (int err) {
						printError(err);
					}
					catch (out_of_range) {
						printError(-2);
					}
				}
			}
			else {
				cout << "тぃ跑计" << endl;
			}
		}
		else
			break;
	}
}

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