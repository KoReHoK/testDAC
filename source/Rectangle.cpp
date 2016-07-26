#include "C:\Users\Andrey\Desktop\Linearization\Linerization\Working Test\version 1.1\include\Rectangle.h"


Rectangle::Rectangle()
{	
	for (int i = 0; i < diskret; i++)
		val[i] = 0x0;
}

Rectangle::~Rectangle(void)
{
}


//------------------------------------------------------------------------------------------------
// инициализирует массив значений сигнала меандр
void Rectangle::setVal(float _diap) {

	int x = symmetry*diskret/100;
	uint16_t value;

	for (int i = 0; i < x ; i++)
	{

		value = (2*amplitude + offsetY) * 0xFFFF / _diap;
		if (value>0xFFFF) value = 0xFFFF;
		if (value<0x0) value = 0x0;
	
		val[i] = value & 0xFFFF;
	}

	for (int i = x; i < diskret; i++)
	{

		value = offsetY * 0xFFFF / _diap;
		if (value>0xFFFF) value = 0xFFFF;
		if (value<0x0) value = 0x0;

		val[i] = value & 0xFFFF;
	}

}