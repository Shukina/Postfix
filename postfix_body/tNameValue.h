#pragma once
#ifndef _NAMEVALUE_H
#define _NAMEVALUE_H
//#include <string>
#include <iostream>
using namespace std;

class NameValue
{
	string name; // ��� �������� 
	float value; // �������� �������� 
public:
	NameValue():name(NULL), value(NULL) {};
	NameValue(string _name, float _value)
	{
		name = _name;
		value = _value;
	}
	string GetName() // �������� ��� ����������
	{
		return name;
	}

	float GetValue() // �������� �������� ����������
	{
		return value;
	}
	void SetValue(float _value)// ������ �������� ����������
	{
		value = _value;
	}

};
#endif