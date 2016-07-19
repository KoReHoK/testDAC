#pragma once
#include "signal.h"
class Triangle : 
	public Signal
{
public:

	Triangle(double, double, double);	// _minVal, _maxVal, OffsetX
	~Triangle(void);

	void setVal(double);				// инициализирует массив значений сигнала треугольник

};
