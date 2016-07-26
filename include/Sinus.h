#pragma once
#include "C:\Users\Andrey\Desktop\Linearization\Linerization\Working Test\version 1.1\include\signal.h"
class Sinus : 
	public Signal
{
public:

	Sinus();	
	~Sinus(void);

	void setVal(float);			// инициализирует массив значений сигнала sin(x)

};

