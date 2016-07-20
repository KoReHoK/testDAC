#include "C:\Users\Andrey\Desktop\Linerization\Working Test\testDAC\include\Triangle.h"


Triangle::Triangle(float _minVal, float _maxVal, float _setX, uint16_t _freq, uint16_t _cycles, int _symmetry)
{
	setSymmetry(_symmetry);
	setParam(_minVal, _maxVal);		// _minVal, _maxVal "размах" сигнала в вольтах
	setOffsetX(_setX);				// выставляет начальную фазу (в градусах)
	setFrequence(_freq);			// выставляет частоту сигнала
	setCycles(_cycles);				// выставляет число генерируемых периодов ( 0 - continium mode )
}

Triangle::~Triangle()
{
}

//--------------------------------------------------------

void Triangle::setSymmetry(int _sym)
{
	symmetry = _sym;
}

int Triangle::getSymmetry(void)
{
	return int(symmetry);
}

void Triangle::setAmplitude(float _ampl) {
	amplitude = 2*_ampl;
}



//------------------------------------------------------------------------------------------------
// инициализирует массив значений сигнала треугольник
void Triangle::setVal(float _diap) {

	int Xb = symmetry*diskret/100;
	uint16_t value;

	for (int i=0; i<Xb; i++)
	{
		value = (offsetY + (amplitude / Xb)*i) * 0xFFFF / _diap;
		if (value>0xFFFF) value=0xFFFF;
		if (value<0x0) value=0x0;

		val[i] = value&0xFFFF;

	}

	int Xc = diskret;
	for (int i = 0; i < (Xc - Xb); i++)
	{
		
		value = val[Xb-1] - ((amplitude/(Xc - Xb))*i)* 0xFFFF / _diap;
		if (value>0xFFFF) value = 0xFFFF;
		if (value<0x0) value = 0x0;

		val[Xb+i] = value & 0xFFFF;

	}
}
