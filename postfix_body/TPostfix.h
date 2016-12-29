#pragma once
#ifndef _POSTFiIXS_H
#define _POSTFiIXS_H

#include "tstack.h"
#include <string>
#include <iostream>

using namespace std;

class TPostfix
{
private:
	string infix;
	string postfix;
	string *TOperations;
	 int *TPriority;
	 double result=0;
//служебные методы(закрытые)
	
	
	
public:
	TPostfix(string _str)
	{
		infix = _str;
		postfix = "Not Exist";
		//MadeTable(TOperations,TPriority); //заполним таблицу операций и приоритетов
		//string TOperations[8]; //операции
		TOperations = new string[8];
		TOperations[0] = '+';
		TOperations[1] = '-';
		TOperations[2] = '*';
		TOperations[3] = '/';
		TOperations[4] = "sin";
		TOperations[5] = "cos";
		TOperations[6] = '(';
		TOperations[7] = ')';


		//int TPriority[8];		//приоритет
		TPriority = new int[8];
		TPriority[0] = 1;
		TPriority[1] = 1;
		TPriority[2] = 2;
		TPriority[3] = 2;
		TPriority[4] = 3;
		TPriority[5] = 3;
		TPriority[6] = 0;
		TPriority[7] = 0;
	};
	bool IsCorrect(string &str) //проверка на корректность введённой строки
	{
		char now;
		int size = str.size();
		for (int i = 0; i < size; i++)
		{
			now = str[i];
			if (!(((now > 39) && (now < 58)) || ((now > 64) && (now < 91)) || ((now > 96) && (now < 123))))
			{
				cout << "Введён недопустимый символ на " << i + 1 << " позиции" << endl;
				throw 'b';
				return 0;
			}
			if (now == 46)
				str[i] = ',';
		}

		
		int left = 0;
		int right = 0;
		for (size_t i = 0; i < str.length(); i++) //проверяем количество ( и ) (они должны быть равны)
		{
			if (str[i] == '(')
				left++;
			if (str[i] == ')')
				right++;
		}
		if (left != right)
			return false;
		char temp;
		for (size_t i = 1; i < (str.length()) - 1; i++) //проверяем все символы, кроме 1ой и последней позиции(их уже проверили)
		{
			temp = str[i];
			if (!((39 < temp) && (temp < 58) || (64 < temp) && (temp > 91) || (96 < temp) && (temp < 123)))// если элемент !=операции+числа, 'A-Z', 'a-z'
				return false;
			if (temp == 46)
				str[i] = ',';
		}
		string bad[25];//некоректная запись операций
		bad[0] = "(+";
		bad[1] = "(-";
		bad[2] = "(*";
		bad[3] = "(/";
		bad[4] = "()";
		bad[5] = "++";
		bad[6] = "+-";
		bad[7] = "+*";
		bad[8] = "+/";
		bad[9] = "+)";
		bad[10] = "-+";
		bad[11] = "--";
		bad[12] = "-*";
		bad[13] = "-/";
		bad[14] = "-)";
		bad[15] = "*+";
		bad[16] = "*-";
		bad[17] = "**";
		bad[18] = "*/";
		bad[19] = "*)";
		bad[20] = "/+";
		bad[21] = "/-";
		bad[22] = "/*";
		bad[23] = "//";
		bad[24] = "/)";
		for (int i = 0; i < 25; i++)//проверка на отсутствие неверно записанных операций
			if (str.find(bad[i]) != -1)
				return false;
		return true;
	}
	
	int IsOperation(string &Str, int &i, string *TOperations)//close проверка на операцию, возвращает индекс операции в TOperations или -1, если это не операция
{
		if (i > Str.length())
			throw 'b';
		else
		{
			for (int j = 0; j < 8; j++)
				if (Str[i] == TOperations[j][0])
				{
					if (j == 4)
						if (Str.substr(i, 3) == "sin")//substr(i,j)-читает строчку str с i-го элемента j элементов
							return 4;
						else
							break;
					if (j == 5)
						if (Str.substr(i, 3) == "cos")
							return 5;
						else
							break;
					return j;
				}
			return -1;
		}
} 
	int PrOperation(string &Str, string *TOperations, int* TPriority)//получает операцию(Str) возвращает ее приоритет
	{
		int temp = 0;
		for (int i = 0; i < 8; i++)
		{
			if (Str == TOperations[i])
				return TPriority[i];
			else
				temp++;
		}
		if (temp == 8)
			return -1;
	}

	void ToPostfix()
{
		//MadeTable(TOperations, TPriority);
	string tmpstr = infix;//дублер для infix
	TStack<string> OperationsStack;//стэк для операций
	string result;//дублер для postfix
	string temp, OperationTop;//temp-текущая операция, OperationTop-верхняя(на данный момент операция)
	int OperationIndex;//индекс операции в таблице операций(TOperations)
	int size = tmpstr.size();
	for (int i = 0; i<size; i++)
	{
		if (tmpstr[i] == '(')//обработка ( скобки
		{
			OperationsStack.Push("(");
			continue;
		}
		if (tmpstr[i] == ')')//обработка ) скобки
		{
			temp = OperationsStack.Pop();
			while (temp != "(")
			{
				result += temp;
				temp = OperationsStack.Pop();
			}
			continue;
		}
		OperationIndex = IsOperation(tmpstr, i, TOperations);
		if (OperationIndex > -1)
		{
			if (OperationIndex > 3)//?
				i = i + 2;
			if (OperationsStack.IsEmpty())
			{
				OperationsStack.Push(TOperations[OperationIndex]);
				continue;
			}
			temp = TOperations[OperationIndex];
			OperationTop = OperationsStack.Pop();
			while (PrOperation(temp, TOperations, TPriority) <= PrOperation(OperationTop, TOperations, TPriority))
			{
				result += OperationTop;
				if (OperationsStack.IsEmpty())
					break;
				OperationTop = OperationsStack.Pop();
			}
			if (PrOperation(temp, TOperations, TPriority) > PrOperation(OperationTop, TOperations, TPriority))
				OperationsStack.Push(OperationTop);
			OperationsStack.Push(temp);
		}
		else//элемент-операнд(не операция)
		{
			int len = 0;//длина подряд идущих операндов
			int pos = i;//позиция, на которой встретился операнд
			do
			{
				len++;
				pos++;
				OperationIndex = IsOperation(tmpstr, pos, TOperations);
				if (pos == size)
					break;
			} while (OperationIndex == -1);
			result += tmpstr.substr(i, len) + " ";
			i = i + len - 1;
		}
	}
	while (OperationsStack.IsEmpty() != true)
		result += OperationsStack.Pop();
	postfix = result;
}


	double Calculate()
{
	if (postfix == "Not Exist")
		throw("postfix_not_exist");
	TStack<double> CalculatingStack;//запишем туда операнды
	//TStack<string> CalculatingStack2;//запишем туда операции
	//int OperationIndex;
	int i = 0, len = 0;
	double temp = 0;
	int flag = 0;
	double a = 0;
	double temp2, first = 0, second = 0;
	string str;
	int size = postfix.length();
	for(int i=0;i<postfix.length();i++)
	{
		int OperationIndex = IsOperation(postfix, i, TOperations);
		if (postfix[i] == ' ')
			continue;
		
		if (OperationIndex == -1 )
		{
			len = 0;
			do
			{
				len++;
				if (i + len == size)
					break;
			} while (postfix[i + len] != ' ');
			str = postfix.substr(i, len);
			temp2 = atof(str.c_str());
			i = i + len;
			CalculatingStack.Push(temp2);
		}
			if (OperationIndex == 0)
			{
				second = CalculatingStack.Pop();
				first = CalculatingStack.Pop();
				CalculatingStack.Push(first + second);
				continue;
			}
			if (OperationIndex == 1)
			{
				second = CalculatingStack.Pop();
				if (CalculatingStack.IsEmpty()||second<0)
					first = 0;
				else
					first = CalculatingStack.Pop();
				CalculatingStack.Push(first - second);
				continue;
			}
			if (OperationIndex == 2)
			{
				second = CalculatingStack.Pop();
				first = CalculatingStack.Pop();
				CalculatingStack.Push(first * second);
				continue;
			}
			if (OperationIndex == 3)
			{
				
				second = CalculatingStack.Pop();
				first = CalculatingStack.Pop();

				if (second == 0)
					throw 'd0';
				else
					CalculatingStack.Push(first / second);
				continue;
			}
			if (OperationIndex == 4)
			{
				i = i + 2;
				CalculatingStack.Push(sin((CalculatingStack.Pop())*3.1415/180));
				continue;
			}
			if (OperationIndex == 5)
			{
				i = i + 2;
				CalculatingStack.Push(cos((CalculatingStack.Pop())*3.1415 / 180));
				continue;
			}
		//}
}
result = CalculatingStack.Pop();
return result;
}
	string GetInfix()
	{
		return infix;
	}

	string GetPostfix()
	{
		return postfix;
	}
	
};

#endif