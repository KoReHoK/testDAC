#include "C:\Users\Andrey\Desktop\Linerization\Working Test\testDAC\include\Sinus.h"
#include <math.h>


Sinus::Sinus(float _minVal, float _maxVal, float _setX, uint16_t _freq, uint16_t _cycles)
{
	setParam(_minVal, _maxVal);				// _minVal, _maxVal "размах" сигнала в вольтах
	setOffsetX(_setX);						// выставляет начальную фазу (в градусах)
	setFrequence(_freq);					// выставляет частоту сигнала
	setCycles(_cycles);						// выставляет число генерируемых периодов ( 0 - continium mode )
}

Sinus::~Sinus()
{
}

//----------------------------------------------------------------------------
void Sinus::setAmplitude(float _ampl) {
	amplitude = _ampl;
}

//------------------------------------------------------------------------------------------------
// инициализирует массив значений сигнала sin(x)
void Sinus::setVal(float _diap) {

	double rad;
	uint16_t value;

	rad = 2 * PI / diskret;

	for (int i = 0; i<diskret; i++)
	{

		value = (amplitude*(sin(i * rad) + 1) + offsetY) * 0xFFFF / _diap;
		if (value>0xFFFF) value = 0xFFFF;
		if (value<0x0) value = 0x0;

		val[i] = value & 0xFFFF;

	}
}
