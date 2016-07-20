#pragma once
#include "signal.h"
class Sinus : 
	public Signal
{
public:

	Sinus(float, float, float, uint16_t, uint16_t);	// _minVal, _maxVal, _offsetX, _frequence, _cycles 
	~Sinus(void);

	void setAmplitude(float);
	void setVal(float);			// инициализирует массив значений сигнала sin(x)

};

