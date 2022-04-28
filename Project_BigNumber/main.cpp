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
		case -2:   //��J���~
			NumberObject::printError(-2);
			break;
		case -1:   //�䤣���ܼ�
			NumberObject::printError(4);
			break;
		case 1:   //�]�w�ܼ�
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
				if (condition == 2) {   //���
					Integer integer = input.c_str();
					cout << integer << endl;
				}
				else if (condition == 3) {   //�p��	
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
