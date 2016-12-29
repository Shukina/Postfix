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
		cout << "Введите арифметическое выражение: ";
		cin >> expression;
		if (expression == "0")
			break;
		TPostfix postfix(expression);
		postfix.IsCorrect(expression);
		cout << expression << endl;
		postfix = expression;
		cout << "Арифметическое выражение: " << expression << endl;

		postfix.ToPostfix();
		cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
		res = postfix.Calculate();
		cout << res << endl;
	}

	return 0;
}