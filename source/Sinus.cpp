#include "C:\Users\Andrey\Desktop\Linerization\Working Test\testDAC\include\Sinus.h"
#include <math.h>


Sinus::Sinus(double _minVal, double _maxVal, double _setX)
{
	setParam(_minVal, _maxVal);				// _minVal, _maxVal "размах" сигнала в вольтах
	setOffsetX(_setX);						// выставляет начальную фазу (в градусах)
}

Sinus::~Sinus()
{
}


//------------------------------------------------------------------------------------------------
// инициализирует массив значений сигнала sin(x)
void Sinus::setVal(double _diap) {

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
