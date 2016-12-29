#pragma once
#ifndef _NAMEVALUE_H
#define _NAMEVALUE_H
//#include <string>
#include <iostream>
using namespace std;

class NameValue
{
	string name; // имя элемента 
	float value; // значение элемента 
public:
	NameValue():name(NULL), value(NULL) {};
	NameValue(string _name, float _value)
	{
		name = _name;
		value = _value;
	}
	string GetName() // Получить имя переменной
	{
		return name;
	}

	float GetValue() // Получить значение переменной
	{
		return value;
	}
	void SetValue(float _value)// Задать значение переменной
	{
		value = _value;
	}

};
#endif