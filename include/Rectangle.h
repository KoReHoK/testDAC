#pragma once
#include "C:\Users\Andrey\Desktop\Linerization\Working Test\testDAC\include\signal.h"
class Rectangle :
	public Signal
{
private:
	int symmetry;
public:

	Rectangle(float, float, float, uint16_t, uint16_t, int);	// _minVal, _maxVal, _offsetX, _frequence, _cycles, _symmetry
	~Rectangle(void);

	void setSymmetry(int);
	int getSymmetry(void);

	void setAmplitude(float);
	void setVal(float);				// инициализирует массив значений сигнала меандр

};

