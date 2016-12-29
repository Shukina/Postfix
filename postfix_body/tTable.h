#pragma once
#ifndef _TABLE_H
#define _TABLE_H
#include "tNameValue.h"

#define SizeMemElem 25; //максимальный размер таблицы
class Table
{
private:
	int Size;//максимальный размер таблицы 
	int Count;//количество элементов в таблице
public:
	NameValue* pTable;//указатель на элементы таблицы 
	Table(int _Size = 0)	// Конструктор инициализации
	{
		Size = _Size;
		Count = 0;
		pTable = new NameValue [Size];
	}

	~Table(void) // Деструктор
	{
		delete[] pTable;
	}

	int GetNumberString(string _Name) // Получить номер строки таблицы по имени
	{
		int temp = -1;
		for (int i = 0; Count < i; i++)
		{
			if (pTable[i].GetName() == _Name)
				temp = i;
		}
		return temp;
	}

	void SetString(string _Name, float _Value)	// Задать строку таблицы =0
	{
		int temp = -1;
		if (temp = GetNumberString(_Name) >= 0)
			pTable[temp].SetValue(_Value);
		else
		{
			if (Count <= 0)
			{
				NameValue tmp(_Name, _Value);
				pTable[Count++] = tmp;
				//delete tmp;
			}
			else
				throw 'not';
		}
	}

		float GetValue(string _Name)	// Получить значение строки таблицы
		{
			return pTable[GetNumberString(_Name)].GetValue();
		}

		void DeleteString(string _Name)	// Удаление строки таблицы
		{
			int temp = -1;
			if (temp = GetNumberString(_Name) >= 0)
				pTable[temp] = pTable[Count--];
		}
		
		bool IsEmpty()	// Проверка заполненности
		{
			if (Count == 0)
				return true;
			else
				return false;
		}

		bool IsFull()	// Проверка пустоты
		{
			if (Count == Size)
				return true;
			else
				return false;
		}

		string GetNameTab(int i)	// Получить название переменной i-ой строки
		{
			if ((i >= 0) && (i <= Count))
				return pTable[i].GetName();
			else
				throw 'not';
		}

		void SetValueTab(int i, float _Value)	// Задать значение переменной элемента i-ой строки
		{
			if ((i >= 0) && (i <= Count))
				pTable[i].SetValue(_Value);
			else
				throw 'not';
		}

		int GetCount() //Проверка полноты
		{
			return Count;
		}

};

#endif