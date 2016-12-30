#pragma once
#ifndef _TSTACK_H
#define _TSTACK_H

const int START_SIZE = 50;//������ ������ �� ���������
const int MAX_SIZE = 102400;

template<class Valtype>
class TStack
{
protected:
	Valtype *pStack; //������ ��� �����
	int Size;
	int Index; //������ ���������� �������� ��������
public:
	TStack();
	TStack(int _Size);
	//TStack(const TStack &v);  // ����������� �����������
	~TStack();
	bool IsEmpty(); // ���� �� ����?
	bool IsFull(); // ����� �� ����?
	void Push(Valtype val); //�������� ������� 
	Valtype Pop(); // ������� �������� �������� � ������� ��� �� ����� 
	Valtype Show(); // ������� �������� ��������, �� ������ ��� �� ����� 
};

template<class Valtype>
TStack<Valtype>::TStack()
{
	Size = START_SIZE;
	Index = -1;
	pStack = new Valtype[Size];
}

template<class Valtype>
TStack<Valtype>::TStack(int _Size)
{
	if (_Size<1 || _Size>MAX_SIZE)
		throw ("not right size");
	else
	{
		Size = _Size;
		Index = -1;
		pStack = new Valtype[Size];
	}
}

template<class Valtype>
TStack<Valtype>::~TStack()
{
	delete[] pStack;
}

template<class Valtype>
bool TStack<Valtype>::IsEmpty() //�������� �������	
{
	if (Index == -1)
		return true;
	else
		return false;
}


template<class Valtype>
bool TStack<Valtype>::IsFull() //�������� �������
{
	if (Index == Size - 1)
		return true;
	else
		return false;
}


template<class Valtype>
void TStack<Valtype>::Push(Valtype val) //�������� �������
{
	if (IsFull() == true)
		throw'n_i';
	else
		pStack[++Index] = val;
}

template<class Valtype>
Valtype TStack<Valtype>::Pop() //������� �������
{
	return pStack[Index--];
}

template<class Valtype>
Valtype TStack<Valtype>::Show() //�������� ��������� �������
{
	return pStack[Index - 1];
}

#endif