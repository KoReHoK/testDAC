#pragma once
#include "c:\users\andrey\desktop\linerization\working test\testdac\include\signal.h"
class Rectangle :
	public Signal
{
public:

	Rectangle(double, double, double);	// _minVal, _maxVal, OffsetX
	~Rectangle(void);

	void setVal(double);				// инициализирует массив значений сигнала меандр

};

