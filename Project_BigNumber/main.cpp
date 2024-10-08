#include "NumberObject.h"
#include "Decimal.h"
#include "Integer.h"

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
			try {
				NumberObject::replaceVariables(input);
				NumberObject::setVariables(input);
			}
			catch (int err) {
				NumberObject::printError(err);
			}
			catch (out_of_range) {
				NumberObject::printError(-2);
			}
			break;
		case 2:
		case 3:
			try {
				NumberObject::replaceVariables(input);
				if (condition == 2) {   //整數
					Decimal decimal = input.c_str();
					Integer integer = (decimal.positive ? "" : "-") + decimal.findExactlyValue();
					string::iterator it = find(integer.fract.numerator.begin(), integer.fract.numerator.end(), '.');
					if (it != integer.fract.numerator.end())
						integer.fract.numerator.erase(it, integer.fract.numerator.end());
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
		case 4:
			try {
				NumberObject::replaceVariables(input);
				NumberObject::setVariables(input);
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
