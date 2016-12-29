#include "TPostfix.h"
//#include "tstack.h"


/*
 string TPostfix::GetInfix()
{
	return infix;
}

string TPostfix::GetPostfix()
{
	return postfix;
}


bool TPostfix::IsCorrect(string &str) //�������� �� ������������ �������� ������
{
	if (!(str[0] == 40 || (65 <= str[0])&&(str[0] <= 90) || (97 <= str[0]) && (str[0] <= 122))) // ���� ������ ������� != '(' 'A'-'Z' 'a'-'z' 
		return false;
	int a = (str.length() - 1);
	if (!( str[a] == 41 || (65 <= str[a]) && (str[a] <= 90) || (97 <= str[a]) && (str[a] <= 122))) // ���� ��������� ������� != ')' 'A'-'Z' 'a'-'z' 
		return false;
	int left = 0;
	int right = 0;
	for (size_t i = 0; i < str.length(); i++) //��������� ���������� ( � ) (��� ������ ���� �����)
	{
		if (str[i] == '(')
			left++;
		if (str[i] == ')')
			right++;
	}
	if (left != right)
		return false;
	char temp;
	for (size_t i = 1; i < (str.length()) - 1; i++) //��������� ��� �������, ����� 1�� � ��������� �������(�� ��� ���������)
	{
		temp = str[i];
		if (!((39 < temp)&&(temp < 58) || (64 < temp)&&(temp > 91) || (96 < temp)&&(temp < 123)))// ���� ������� !=��������+�����, 'A-Z', 'a-z'
			return false;
		if (temp == 46)
			str[i] = ',';
	}
	string bad[25];//����������� ������ ��������
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
	//bad[18] = "**";//
	bad[19] = "*)";
	bad[20] = "/+";
	bad[21] = "/-";
	bad[22] = "/*";
	bad[23] = "//";
	bad[24] = "/)";
	for (int i = 0; i < 25; i++)//�������� �� ���������� ������� ���������� ��������
		if (str.find(bad[i]) != -1)
			return false;
	return true;
}

/*void TPostfix::MadeTable()//������� ��������, �� �����������
{
	string TOperations[8]; //��������
	TOperations[0] = '+';
	TOperations[1] = '-';
	TOperations[2] = '*';
	TOperations[3] = '/';
	TOperations[4] = "sin";
	TOperations[5] = "cos";
	TOperations[6] = '(';
	TOperations[7] = ')';
	

	int TPriority[8];		//���������
	TPriority[0] = 1;
	TPriority[1] = 1;
	TPriority[2] = 2;
	TPriority[3] = 2;
	TPriority[4] = 3;
	TPriority[5] = 3;
	TPriority[6] = 0;
	TPriority[7] = 0;
}*/

/*int TPostfix::PrOperation(string &Str, string *TOperations, int* TPriority)//�������� ��������(Str) ���������� �� ���������
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

int TPostfix::IsOperation(string &Str, int &i, string *TOperations)//�������� �� ��������, ���������� ������ �������� � TOperations ��� -1, ���� ��� �� ��������
{
	for (int j = 0; j<8; j++)
		if (Str[i] == TOperations[j][0])
		{
			if (j == 4)
				if (Str.substr(i, 3) == "sin")//substr(i,j)-������ ������� str � i-�� �������� j ���������
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

void TPostfix::ToPostfix()
{
	string Str = infix;
	TStack<string> OperationsStack;
	string result;
	string now, OperationTop;
	int i, p, m, OperationIndex;
	int size = Str.size();
	for (i = 0; i<size; i++)
	{
		if (Str[i] == '(')
		{
			OperationsStack.Push("(");
			continue;
		}
		if (Str[i] == ')')
		{
			now = OperationsStack.Pop();
			while (now != "(")
			{
				result += now;
				now = OperationsStack.Pop();
			}
			continue;
		}
		OperationIndex = IsOperation(Str, i, TOperations);
		if (OperationIndex > -1)
		{
			if (OperationIndex > 3)
				i = i + 2;
			if (OperationsStack.IsEmpty())
			{
				OperationsStack.Push(TOperations[OperationIndex]);
				continue;
			}
			now = TOperations[OperationIndex];
			OperationTop = OperationsStack.Pop();
			while (PrOperation(now,TOperations, TPriority) <= PrOperation(OperationTop, TOperations,TPriority))
			{
				result += OperationTop;
				if (OperationsStack.IsEmpty())
					break;
				OperationTop = OperationsStack.Pop();
			}
			if (PrOperation(now, TOperations, TPriority) > PrOperation(OperationTop, TOperations, TPriority))
				OperationsStack.Push(OperationTop);
			OperationsStack.Push(now);
		}
		else
		{
			p = 0;
			m = i;
			do
			{
				p++;
				m++;
				OperationIndex = IsOperation(Str, m, TOperations);
				if (m == size)
					break;
			} while (OperationIndex == -1);
			result += Str.substr(i, p) + " ";
			i = i + p - 1;
		}
	}
	while (!OperationsStack.IsEmpty())
		result += OperationsStack.Pop();
	postfix = result;
}

/*void TPostfix::ToPostfix()
{
	string tmpstr = infix;//������ ��� infix
	TStack<string> OperationsStack;//���� ��� ��������
	string result;//������ ��� postfix
	string temp, OperationTop;//temp-������� ��������, OperationTop-�������(�� ������ ������ ��������)
	int OperationIndex;//������ �������� � ������� ��������(TOperations)
	int size = tmpstr.size();
	for (int i = 0; i<size; i++)
	{
		if (tmpstr[i] == '(')//��������� ( ������
		{
			OperationsStack.Push("(");
			continue;
		}
		if (tmpstr[i] == ')')//��������� ) ������
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
		else//�������-�������(�� ��������)
		{
			int len = 0;//����� ������ ������ ���������
			int pos = i;//�������, �� ������� ���������� �������
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
*/

/*

double TPostfix::Calculate()
{
	if (postfix == "Not Exist")
		throw("postfix_not_exist");
	TStack<double> CalculatingStack;
	int OperationIndex;
	int size = postfix.size();

	double Var1, Var2;
	int i, p, j, check;
	int amount = 0;
	char * Str2;
	string Str;
	string MassiveOfVariables[5000];
	double MassiveOfValues[5000];
	

	for (i = 0; i < size; i++)
	{
		OperationIndex = IsOperation(postfix, i, TOperations);
		if (OperationIndex == -1)//���� �������-�������
		{
			int len = 0;//����� ������ ������ ���������
			do
			{
				len++;
				if (i + len == size)
					break;
			} while (postfix[i + len] != ' ');

			check = 0;
			for (j = 0; j < amount; j++)
				if (postfix.substr(i, p) == MassiveOfVariables[j])
					check = 1;

			Str = postfix.substr(i, len); //������ �� ������ ������ ���������
			Str2 = new char[Str.size() + 1]; //������ �� char ��� �������� ���������
			for (j = 0; j < Str.size() + 1; j++)
				Str2[j] = Str[j];
			Var1 = strtod(Str2, NULL);//������� strtod() ���������� � double ������ ������������� �����, ������������ ��� ����������� �������
			if ((Str2[0] != '0') && (Var1 == 0.0))
				Var1 = Var1 - 1;
			if (check == 0)
			{
				if (Var1 == -1.0)
				{
					cout << "������� �������� ���������� " << Str << " ";
					cin >> MassiveOfValues[amount];
					MassiveOfVariables[amount] = (Str);
					amount++;
				}
				else
				{
					MassiveOfValues[amount] = Var1;
					MassiveOfVariables[amount] = (Str);
					amount++;
				}
			}
			i = i + p;
		}
		if (OperationIndex > 3)
			i = i + 2;
	}
	for (i = 0; i < size; i++)
	{
		OperationIndex = IsOperation(postfix, i,TOperations);
		if (OperationIndex == -1)
		{
			p = 0;
			do
			{
				p++;
				if (i + p == size)
					break;
			} while (postfix[i + p] != ' ');
			Str = postfix.substr(i, p);
			j = 0;
			while (Str != MassiveOfVariables[j])
				j++;
			CalculatingStack.Push(MassiveOfValues[j]);
			i = i + p;
		}
		else
		{
			Var1 = CalculatingStack.Pop();
			if (OperationIndex == 4)
			{
				i = i + 2;
				CalculatingStack.Push(sin((Var1*3.14159265) / 180));
				continue;
			}
			if (OperationIndex == 5)
			{
				i = i + 2;
				CalculatingStack.Push(cos((Var1*3.14159265) / 180));
				continue;
			}
			Var2 = CalculatingStack.Pop();
			switch (OperationIndex)
			{
			case 0:
			{
				Var1 += Var2;
				CalculatingStack.Push(Var1);
				break;
			}
			case 1:
			{
				Var1 = Var2 - Var1;
				CalculatingStack.Push(Var1);
				break;
			}
			case 2:
			{
				Var1 *= Var2;
				CalculatingStack.Push(Var1);
				break;
			}
			case 3:
			{
				if (Var1 == 0)
				{
					cout << "������: � �������� ���������� ���������� ������� �� 0" << endl;
					return 0;
				}
				Var1 = Var2 / Var1;
				CalculatingStack.Push(Var1);
				break;
			}
			}
		}
	}
	return CalculatingStack.Pop();
}



double TPostfix::Calculate()
{
	if (postfix == "Not Exist")
		throw("postfix_not_exist");
	TStack<double> CalculatingStack;//������� ���� ��������
	TStack<string> CalculatingStack2;//������� ���� ��������
	int OperationIndex;

	int i = 0;
	double temp = 0;
	while (postfix[i] != ' ')
	{
		OperationIndex = IsOperation(postfix, i, TOperations);
		if (OperationIndex == -1)//�� ��������
		{
			if (!((47 < postfix[i])&&(postfix[i] < 58)))//���� ������� �� ����(�� ����������)
			{
				cout << "������� �������� ���������� " << postfix[i] << " ";
				cin >> temp;
				CalculatingStack.Push(temp);//������ ���������� ��������� �� ��������
			}
			else
				CalculatingStack.Push(postfix[i]);// ��������� �������� ����������
		}
		else
		{
			/*if (OperationIndex == 4)
			{
				CalculatingStack.Push('sin');
				continue;
			}
			if (OperationIndex == 5)
			{
				CalculatingStack.Push('cos');
				continue;
			}
			if (0<= OperationIndex < 4)
			CalculatingStack2.Push(TOperations[OperationIndex]);
		}		
		i++;
	}


double first = 0, second = 0;
while(!(CalculatingStack2.IsEmpty()))
{
	string tmp = CalculatingStack2.Pop();
	if (tmp == "+")
	{
		second = CalculatingStack.Pop();
		first = CalculatingStack.Pop();
		CalculatingStack.Push(first + second);
		continue;
	}
	if (tmp == "-")
	{
		second = CalculatingStack.Pop();
		first = CalculatingStack.Pop();
		CalculatingStack.Push(first - second);
		continue;
	}
	if (tmp == "*")
	{
		second = CalculatingStack.Pop();
		first = CalculatingStack.Pop();
		CalculatingStack.Push(first * second);
		continue;
	}
	if (tmp == "/")
	{
		second = CalculatingStack.Pop();
		first = CalculatingStack.Pop();
		
		if (second == 0)
			throw 'd0';
		else
			CalculatingStack.Push(first / second);
		continue;
	}
	if (tmp == "^")
	{
		second = CalculatingStack.Pop();
		first = CalculatingStack.Pop();
		CalculatingStack.Push(exp(second*log(first)));
		continue;
	}
	if (tmp == "sin")
	{
		CalculatingStack.Push(sin(CalculatingStack.Pop()));
		continue;
	}
	if (tmp == "cos")
	{
		CalculatingStack.Push(cos(CalculatingStack.Pop()));
		continue;
	}
}
result = CalculatingStack.Pop();
return result;
}
*/

