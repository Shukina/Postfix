#pragma once
#ifndef _TSTACK_H
#define _TSTACK_H

const int START_SIZE = 50;//размер памяти по умолчанию
const int MAX_SIZE = 102400;

template<class Valtype>
class TStack
{
protected:
	Valtype *pStack; //массив для стека
	int Size;
	int Index; //индекс последнего занятого элемента
public:
	TStack();
	TStack(int _Size);
	//TStack(const TStack &v);  // конструктор копирования
	~TStack();
	bool IsEmpty(); // пуст ли стек?
	bool IsFull(); // полон ли стек?
	void Push(Valtype val); //добавить элемент 
	Valtype Pop(); // вернуть значение верхнего и удалить его из стека 
	Valtype Show(); // вернуть значение верхнего, не удаляя его из стека 
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
bool TStack<Valtype>::IsEmpty() //проверка пустоты	
{
	if (Index == -1)
		return true;
	else
		return false;
}


template<class Valtype>
bool TStack<Valtype>::IsFull() //проверка полноты
{
	if (Index == Size - 1)
		return true;
	else
		return false;
}


template<class Valtype>
void TStack<Valtype>::Push(Valtype val) //добавить элемент
{
	if (IsFull() == true)
		throw'n_i';
	else
		pStack[++Index] = val;
}

template<class Valtype>
Valtype TStack<Valtype>::Pop() //достать элемент
{
	return pStack[Index--];
}

template<class Valtype>
Valtype TStack<Valtype>::Show() //показать последний элемент
{
	return pStack[Index - 1];
}

#endif