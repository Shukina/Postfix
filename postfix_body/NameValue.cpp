#include "NameValue.h"

NameValue::NameValue(string _name, float _value)
{
	name = _name;
	value = _value; 
}

string NameValue::GetName()
{
	return name;
}

float NameValue::GetValue()
{
	return value;
}

void NameValue::SetValue(float _value)
{
	value = _value;
}
