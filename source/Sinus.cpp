#include "C:\Users\Andrey\Desktop\Linearization\Linerization\Working Test\version 1.1\include\Sinus.h"
#include <math.h>


Sinus::Sinus()
{
	for (int i = 0; i < diskret; i++)
		val[i] = 0x0;
}

Sinus::~Sinus()
{
}


//------------------------------------------------------------------------------------------------
// инициализирует массив значений сигнала sin(x)
void Sinus::setVal(float _diap) {

	double rad;
	uint16_t value;

	rad = radians(360.0 / diskret);

	for (int i = 0; i<diskret; i++)
	{

		value = (amplitude*(sin(i * rad) + 1) + offsetY) * 0xFFFF / _diap;
		if (value>0xFFFF) value = 0xFFFF;
		if (value<0x0) value = 0x0;

		val[i] = value & 0xFFFF;

	}
}
