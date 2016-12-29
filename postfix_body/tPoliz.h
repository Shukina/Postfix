#pragma once
#ifndef _POLIZ_H
#define _POLIZ_H
#include "tstack.h"
#include "tTable.h"


class Tpoliz
{
private:
	int sizepoliz;
	string* poliz;
	TStack <NameValue> *operstack; //���� ��� ��������, ��������� �� ���������
	Table* opertable; //������� �������� � ����������
	Table* tableoperand; //������� ���������� � �� ��������


	void madeTable()	// �������� ������� ��������
	{
		opertable = new Table(5);
		opertable->SetString("+", 1);
		opertable->SetString("-", 1);
		opertable->SetString("*", 2);
		opertable->SetString("/", 2);
		opertable->SetString("^", 3);
		opertable->SetString("cos", 3);
		opertable->SetString("sin", 3);
		//opertable->SetString("(", 0);
		//opertable->SetString(")", -1);
	}
	void workleft()	// ��������� ����� ������
	{
		operstack->Push(NameValue("(", 0));
	}

	void workright()	// ��������� ������ ������
	{
		while ((operstack->Show().GetName()) != "(")
		{
			poliz[++sizepoliz] = operstack->Pop().GetName();	
		}
		operstack->Pop().GetName();
	}

	void delstrszn(string st, string *w, int &k , string ZN)	// ������� ������ � �������� ������� ���������
	{//st-��������� ������, w-�������� ������, 
		string t=st+ '_'; //��������, �������� �������-����� ������
		string zn = ZN;
		k = 0;
		w[k] = "";//��������� �������
		string f;
		for (int i = 0; i < (t.length()); i++)
		{
			f = t[i];
			if (zn.find(f) == -1 || (t[i] == 's' && t[i + 1] == 'i' && t[i + 2] == 'n') || (t[i] == 'c' && t[i + 1] == 'o' && t[i + 2] == 's'))//������� �� �������� ���������
			{
				w[k] = w[k] + t[i];//������ ��������� � string w
			}
			else
			{
				if (t[i] == '_')//���� ������� �������� ������� ������
				{
					if (w[k] != "")//���� � ��������� ������ �� �������
					{
						w[++k] = ""; //��������� �������(����� ��������� ������)
					}
				}
				else //���� ������� �� �������� ������� ������
				{
					if (w[k] != "") //���� � ��������� ������ �� �������
						w[++k] = t[i];//��������� ������� � ��������� ������ ��������� ���������
					else//���� � ��������� ������  �������
						w[k] = t[i];//������ ������� ��������� �������
					w[++k] = "";//��������� ��������� ��������� ��������� �������
				}
			}
		}
	}

	void worklast() // ��������� �����
	{
		while ((operstack->IsEmpty()) != true)
		{
			poliz[++sizepoliz] = operstack->Pop().GetName();
		}
	}

	void workoperation(string *Lex, int prior)	// ��������� ��������
	{
		if (operstack->IsEmpty() == true)
			operstack->Push(NameValue(*Lex, prior));
		else
		{
			while (operstack->Show().GetValue() >= prior)
				poliz[++sizepoliz] = operstack->Pop().GetName();
		}
		operstack->Push(NameValue(*Lex, prior));
	}

	void workoperand(string *Lex)	// ��������� ��������
	{
		for (int i = 0; i<1; i++)
		{
			//atof(s1) ����������� ������ s1 � ��� double
			//c_str() ���������� ��������� �� ���������� ������
			poliz[++sizepoliz] = Lex[i];
			if ((atof(Lex[i].c_str()) >= 0) || (atof(Lex[i].c_str())<0))
				tableoperand->SetString(*Lex, atof(Lex[i].c_str()));
			else
				tableoperand->SetString(*Lex, 0);
		}

		//  ???
	
	}
	

public:
	Tpoliz(string _str = "")	// ����������� �������������
	{
		operstack = new TStack<NameValue>(_str.length() / 2);
		madeTable();
		madePoliz(_str);
	}

	string* GetPoliz()
	{
		return poliz;
	}

	void madePoliz(string str)	// �������� ������
	{
		int f = str.length(), sizeLex = 0;
		string zn = "_+-*/^()";
		string* Lex = new string[f + 1]; delstrszn(str, Lex, sizeLex, zn);
		poliz = new string[sizeLex + 2];	// �������� � �������
		sizepoliz = 0;	//����� ������
		tableoperand = new Table(((sizeLex) / 2) + 1);	// �������� � �������
		int pr = 0;
		for (int i = 0; i<(sizeLex + 1); i++)
		{
			if (Lex[i] == "(") workleft();
			else {
				if (Lex[i] == ")") workright();
				else {
					pr = opertable->GetValue(Lex[i]);
					if ((pr >= 1) && (pr <= 3))	workoperation(&Lex[i], pr);
					else workoperand(&Lex[i]);
				}
			}
		}
		worklast();
	}
	void MMadePoliz(string _str)
	{
		madePoliz(_str);
	}

	int GetSizePoliz()	// �������� ������ ������
	{
		return sizepoliz;
	}
		
	void MadeTableOperand(float *mas)	// ������� ������� ���������
	{
		for (int i = 0; i < tableoperand->GetCount(); i++)
			tableoperand->SetValueTab(i, mas[i]);	
	}

	string GetElmPoliz(int _elem)	// �������� ������� �� ������
	{
		return poliz[_elem];
	}

	float GetValueTab(string str)	// �������� �������� ���������� 
	{
		return tableoperand->GetValue(str);
	}
	
	string GetNameTabOper(int cur)	// �������� ��� �������� cur
	{
		return tableoperand->GetNameTab(cur);
	}

	int sizeOperTab()	// �������� ������ ������� ���������
	{
		return tableoperand->GetCount();
	}


	~Tpoliz(void)	// ����������
	{
		delete tableoperand;
		delete operstack;
		delete opertable;
		delete[] poliz;
	}

};
#endif
