#include "C:\Users\Andrey\Desktop\Linerization\Working Test\testDAC\include\Rectangle.h"


Rectangle::Rectangle(float _minVal, float _maxVal, float _setX, uint16_t _freq, uint16_t _cycles, int _symmetry)
{
	setSymmetry(_symmetry);	
	setParam(_minVal, _maxVal);		// _minVal, _maxVal "размах" сигнала в вольтах
	setOffsetX(_setX);				// выставляет начальную фазу (в градусах)
	setFrequence(_freq);			// выставляет частоту сигнала
	setCycles(_cycles);				// выставляет число генерируемых периодов ( 0 - continium mode )
}

Rectangle::~Rectangle(void)
{
}

//-------------------------------------------------------------

void Rectangle::setSymmetry(int _sym)
{
	symmetry = _sym;
}

int Rectangle::getSymmetry(void)
{
	return (int)symmetry;
}

void Rectangle::setAmplitude(float _ampl) {
	amplitude = 2 * _ampl;
}



//------------------------------------------------------------------------------------------------
// инициализирует массив значений сигнала меандр
void Rectangle::setVal(float _diap) {

	int x = symmetry*diskret/100;
	uint16_t value;

	for (int i = 0; i < x ; i++)
	{

		value = (amplitude + offsetY) * 0xFFFF / _diap;
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