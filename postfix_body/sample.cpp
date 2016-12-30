#include <iostream>
#include <string>
#include "tPostfix.h"

using namespace std;

int main()
{
	string expression;
	
	double res;

	setlocale(LC_ALL, "Russian");
	while (expression != "0")
	{
		cout << "������� �������������� ���������: ";
		cin >> expression;
		if (expression == "0")
			break;
		TPostfix postfix(expression);
		//postfix.IsCorrect(expression);
		//postfix.CorrectWithUnarMinus();
		//cout << "infix" << << endl;
		//cout << expression << endl;
		//postfix = expression;
		cout << "�������������� ���������: " << postfix.GetInfix() << endl;

		postfix.ToPostfix();
		cout << "����������� �����: " << postfix.GetPostfix() << endl;
		res = postfix.Calculate();
		cout <<"���������: "<< res <<endl<< endl;
	}

	return 0;
}