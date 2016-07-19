#include "c:\users\andrey\desktop\linerization\working test\testdac\include\Rectangle.h"


Rectangle::Rectangle(double _minVal, double _maxVal, double setX)
{
	setParam(_minVal, _maxVal);		// _minVal, _maxVal "размах" сигнала в вольтах
	setOffsetX(setX);				// выставляет начальную фазу (в градусах)
}

Rectangle::~Rectangle(void)
{
}


//------------------------------------------------------------------------------------------------
// инициализирует массив значений сигнала меандр
void Rectangle::setVal(double _diap) {

	uint16_t value;

	for (int i = 0; i < diskret/2 ; i++)
	{

		value = (amplitude + offsetY) * 0xFFFF / _diap;
		if (value>0xFFFF) value = 0xFFFF;
		if (value<0x0) value = 0x0;

		val[i] = value & 0xFFFF;

	}

	for (int i = diskret / 2; i < diskret; i++)
	{

		value = offsetY * 0xFFFF / diap;
		if (value>0xFFFF) value = 0xFFFF;
		if (value<0x0) value = 0x0;

		val[i] = value & 0xFFFF;

	}
}