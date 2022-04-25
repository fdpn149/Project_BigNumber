#include "NumberObject.h"
#include "Decimal.h"
#include "Integer.h"

struct Variable {
	string name;
	string type;
	string value;
};

vector<Variable> variable = { {"abc", "Decimal", "3.14"}, {"defg","Integer","98"}, {"hij", "Decimal", "3.14"} };

int main()
{
	char firstChar;
	string input;
	int condition;
	getline(cin, input);
	condition = NumberObject::inputJudge(input);
	while (condition != 0) {
		switch (condition) {
		case -2:   //輸入有誤
			NumberObject::printError(-2);
			break;
		case -1:   //找不到變數
			NumberObject::printError(4);
			break;
		case 1:   //設定變數
			break;
		case 2:
		case 3:
			try {
				NumberObject::replaceVariables(input);
				if (condition == 2) {   //整數
					Integer integer = input.c_str();
					cout << integer << endl;
				}
				else if (condition == 3) {   //小數	
					Decimal decimal = input.c_str();
					cout << decimal << endl;
				}
			}
			catch (int err) {
				NumberObject::printError(err);
			}
			catch (out_of_range) {
				NumberObject::printError(-2);
			}
			break;
		}

		getline(cin, input);
		condition = NumberObject::inputJudge(input);
	}
}
