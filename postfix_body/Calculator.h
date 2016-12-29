#pragma once
#ifndef _CALCULATOR_H
#define _CALCULATOR_H
#include"tPoliz.h"

class Calculator
{
	Tpoliz *poliz;
	TStack <float> *oper; //стэк для хранения значений элементов
	float result; //переменная для хранения результата
	string str;
public:
	Calculator(string _str)
	{
		str = _str;
	}

	Calculator()
	{
		delete[] poliz;
		delete[] oper;
	}

	string GetString()
	{
		return str;
	}

	void SetTab(float *mas) //задать таблицу операндов
	{
		poliz->MadeTableOperand(mas);
	}

	int GetOper() //получить количество операндов в таблице
	{
		return poliz->sizeOperTab();
	}

	void SetSt(string _str)	// задать строку и составить полиз
	{
		str=_str;
		delete poliz;
		poliz = new Tpoliz(str);
		result = 0;

	}

	string GetPoliz()	// получить Полиз для вывода
	{
		string tmp;
		for (int i = 0; i<(poliz->GetSizePoliz()) + 1; i++)
		{
			tmp += poliz->GetElmPoliz(i);
		}
		return tmp;
	}

	void RezUp()	// Сосчитать результат выражения
	{
		float first = 0, second = 0;
		for (int i = 0; i < (poliz->GetSizePoliz() + 1); i++)
		{
			string tmp = poliz->GetElmPoliz(i);
			if (tmp == "+")
			{
				second = oper->Pop();
				first = oper->Pop();
				oper->Push(first + second);
				continue;
			}
			if (tmp == "-")
			{
				second = oper->Pop();
				first = oper->Pop();
				oper->Push(first - second);
				continue;
			}
			if (tmp == "*")
			{
				second = oper->Pop();
				first = oper->Pop();
				oper->Push(first*second);
				continue;
			}
			if (tmp == "/")
			{
				second = oper->Pop();
				first = oper->Pop();
				if (second == 0)
					throw 'd0';
				else
				    oper->Push(first / second);
				continue;
			}
			if (tmp == "^")
			{
				second = oper->Pop();
				first = oper->Pop();
				oper->Push(exp(second*log(first)));
				continue;
			}
			if (tmp == "sin")
			{
				oper->Push(sin(oper->Pop()));
				continue;
			}
			if (tmp == "cos")
			{
				oper->Push(cos(oper->Pop()));
				continue;
			}
		}
		result = oper->Pop();
	}

	float GetRez()	// Получить результат
	{
		return result;
	}

};


#endif