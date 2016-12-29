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
	TStack <NameValue> *operstack; //стэк дл€ операций, считанных из выражени€
	Table* opertable; //таблица операций и приоритето
	Table* tableoperand; //таблица переменных и их значений


	void madeTable()	// создание таблицы операций
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
	void workleft()	// обработка левой скобки
	{
		operstack->Push(NameValue("(", 0));
	}

	void workright()	// обработка правой скобки
	{
		while ((operstack->Show().GetName()) != "(")
		{
			poliz[++sizepoliz] = operstack->Pop().GetName();	
		}
		operstack->Pop().GetName();
	}

	void delstrszn(string st, string *w, int &k , string ZN)	// деление строки и создани€ массива элементов
	{//st-инфиксна€ запись, w-польска€ запись, 
		string t=st+ '_'; //копируем, добавл€€ элемент-финал строки
		string zn = ZN;
		k = 0;
		w[k] = "";//добавл€ем пустоту
		string f;
		for (int i = 0; i < (t.length()); i++)
		{
			f = t[i];
			if (zn.find(f) == -1 || (t[i] == 's' && t[i + 1] == 'i' && t[i + 2] == 'n') || (t[i] == 'c' && t[i + 1] == 'o' && t[i + 2] == 's'))//элемент не €вл€етс€ операцией
			{
				w[k] = w[k] + t[i];//просто добавл€ем в string w
			}
			else
			{
				if (t[i] == '_')//если элемент €вл€етс€ финалом строки
				{
					if (w[k] != "")//если в финальной строке не пустота
					{
						w[++k] = ""; //длбавл€ем пустоту(финал финальной строки)
					}
				}
				else //если элемент не €вл€етс€ финалом строки
				{
					if (w[k] != "") //если в финальной строке не пустота
						w[++k] = t[i];//добавл€ем элемент в финальную строку следующим элементом
					else//если в финальной строке  пустота
						w[k] = t[i];//вместо пустоты добавл€ем элемент
					w[++k] = "";//следующим элементом добавл€ем финальную пустоту
				}
			}
		}
	}

	void worklast() // обработка конца
	{
		while ((operstack->IsEmpty()) != true)
		{
			poliz[++sizepoliz] = operstack->Pop().GetName();
		}
	}

	void workoperation(string *Lex, int prior)	// обработка операции
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

	void workoperand(string *Lex)	// обработка операнда
	{
		for (int i = 0; i<1; i++)
		{
			//atof(s1) преобразует строку s1 в тип double
			//c_str() возвращает указатель на символьный массив
			poliz[++sizepoliz] = Lex[i];
			if ((atof(Lex[i].c_str()) >= 0) || (atof(Lex[i].c_str())<0))
				tableoperand->SetString(*Lex, atof(Lex[i].c_str()));
			else
				tableoperand->SetString(*Lex, 0);
		}

		//  ???
	
	}
	

public:
	Tpoliz(string _str = "")	//  онструктор инициализации
	{
		operstack = new TStack<NameValue>(_str.length() / 2);
		madeTable();
		madePoliz(_str);
	}

	string* GetPoliz()
	{
		return poliz;
	}

	void madePoliz(string str)	// создание полиза
	{
		int f = str.length(), sizeLex = 0;
		string zn = "_+-*/^()";
		string* Lex = new string[f + 1]; delstrszn(str, Lex, sizeLex, zn);
		poliz = new string[sizeLex + 2];	// проблемы с пам€тью
		sizepoliz = 0;	//смена начала
		tableoperand = new Table(((sizeLex) / 2) + 1);	// проблемы с пам€тью
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

	int GetSizePoliz()	// получить размер ѕолиза
	{
		return sizepoliz;
	}
		
	void MadeTableOperand(float *mas)	// сделать таблицу операндов
	{
		for (int i = 0; i < tableoperand->GetCount(); i++)
			tableoperand->SetValueTab(i, mas[i]);	
	}

	string GetElmPoliz(int _elem)	// получить элемент из ѕолиза
	{
		return poliz[_elem];
	}

	float GetValueTab(string str)	// получить значение переменной 
	{
		return tableoperand->GetValue(str);
	}
	
	string GetNameTabOper(int cur)	// получить им€ элемента cur
	{
		return tableoperand->GetNameTab(cur);
	}

	int sizeOperTab()	// ѕолучить размер таблицы операндов
	{
		return tableoperand->GetCount();
	}


	~Tpoliz(void)	// ƒеструктор
	{
		delete tableoperand;
		delete operstack;
		delete opertable;
		delete[] poliz;
	}

};
#endif
