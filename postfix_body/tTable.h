#pragma once
#ifndef _TABLE_H
#define _TABLE_H
#include "tNameValue.h"

#define SizeMemElem 25; //������������ ������ �������
class Table
{
private:
	int Size;//������������ ������ ������� 
	int Count;//���������� ��������� � �������
public:
	NameValue* pTable;//��������� �� �������� ������� 
	Table(int _Size = 0)	// ����������� �������������
	{
		Size = _Size;
		Count = 0;
		pTable = new NameValue [Size];
	}

	~Table(void) // ����������
	{
		delete[] pTable;
	}

	int GetNumberString(string _Name) // �������� ����� ������ ������� �� �����
	{
		int temp = -1;
		for (int i = 0; Count < i; i++)
		{
			if (pTable[i].GetName() == _Name)
				temp = i;
		}
		return temp;
	}

	void SetString(string _Name, float _Value)	// ������ ������ ������� =0
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

		float GetValue(string _Name)	// �������� �������� ������ �������
		{
			return pTable[GetNumberString(_Name)].GetValue();
		}

		void DeleteString(string _Name)	// �������� ������ �������
		{
			int temp = -1;
			if (temp = GetNumberString(_Name) >= 0)
				pTable[temp] = pTable[Count--];
		}
		
		bool IsEmpty()	// �������� �������������
		{
			if (Count == 0)
				return true;
			else
				return false;
		}

		bool IsFull()	// �������� �������
		{
			if (Count == Size)
				return true;
			else
				return false;
		}

		string GetNameTab(int i)	// �������� �������� ���������� i-�� ������
		{
			if ((i >= 0) && (i <= Count))
				return pTable[i].GetName();
			else
				throw 'not';
		}

		void SetValueTab(int i, float _Value)	// ������ �������� ���������� �������� i-�� ������
		{
			if ((i >= 0) && (i <= Count))
				pTable[i].SetValue(_Value);
			else
				throw 'not';
		}

		int GetCount() //�������� �������
		{
			return Count;
		}

};

#endif