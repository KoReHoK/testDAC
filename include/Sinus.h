#pragma once
#include "signal.h"
class Sinus : 
	public Signal
{
public:

	Sinus(double, double, double);	// _minVal, _maxVal, OffsetX
	~Sinus(void);

	void setVal(double);			// инициализирует массив значений сигнала sin(x)

};

