#include "C:\Users\Andrey\Desktop\Linearization\Linerization\Working Test\version 1.1\include\Triangle.h"


Triangle::Triangle()
{
	for (int i = 0; i < diskret; i++)
		val[i] = 0x0;
}

Triangle::~Triangle()
{
}


//------------------------------------------------------------------------------------------------
// инициализирует массив значений сигнала треугольник
void Triangle::setVal(float _diap) {

	int Xb = symmetry*diskret/100;
	uint16_t value;

	for (int i=0; i<Xb; i++)
	{
		value = (offsetY + (2*amplitude / Xb)*i) * 0xFFFF / _diap;
		if (value>0xFFFF) value=0xFFFF;
		if (value<0x0) value=0x0;

		val[i] = value&0xFFFF;

	}

	int Xc = diskret;
	for (int i = 0; i < (Xc - Xb); i++)
	{
		
		value = val[Xb-1] - ((2*amplitude/(Xc - Xb))*i)* 0xFFFF / _diap;
		if (value>0xFFFF) value = 0xFFFF;
		if (value<0x0) value = 0x0;

		val[Xb+i] = value & 0xFFFF;

	}
}
