#pragma once
#include "signal.h"
class Triangle : 
	public Signal
{
private:
	int symmetry;
public:

	Triangle(float, float, float, uint16_t, uint16_t, int);	// _minVal, _maxVal, _offsetX, _frequence, _cycles, _symmetry
	~Triangle(void);

	void setSymmetry(int);
	int getSymmetry(void);

	void setAmplitude(float);
	void setVal(float);				// инициализирует массив значений сигнала треугольник

};
