#include "c:\users\andrey\desktop\linerization\working test\testdac\include\Rectangle.h"


Rectangle::Rectangle(double _minVal, double _maxVal, double setX)
{
	setParam(_minVal, _maxVal);		// _minVal, _maxVal "размах" сигнала в вольтах
	setOffsetX(setX);				// выставляет начальную фазу (в градусах)
}

Rectangle::~Rectangle(void)
{
}

//--------------------------------------------------------

void Rectangle::setAmplitude(double ampl) {
	amplitude = ampl;
}

void Rectangle::setOffsetY(double setY) {
	offsetY = setY;
}

void Rectangle::setOffsetX(double setX) {
	offsetX = (diskret / 360.0)*setX;		// переводим из градусов в дискреты
}

void Rectangle::setMode(byte _mode) {
	mode = _mode;
}

double Rectangle::getAmplitude(void) const {
	return amplitude;
}

double Rectangle::getOffsetY(void) const {
	return offsetY;
}

uint16_t Rectangle::getOffsetX(void) const {
	return offsetX;
}

uint16_t Rectangle::getVal(int number) const {
	return val[number];
}

byte Rectangle::getMode(void) const {
	return mode;
}

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
// рассчитывает амплитуду и смещение относ. оси OY
// minVal и maxVal задают "размах" сигнала в вольтах
void Rectangle::setParam(double minVal, double maxVal) {

	if (minVal < -10.8) minVal = -10.8;
	if (maxVal > 10.8) maxVal = 10.8;

	double diapason;	// 1: 0-5V, 2: 0-10V, 3: 0-10.8V, 4: +-5V, 5: +-10V, 6: +-10.8V
	if (minVal >= 0.0)
	{
		setMode(3);
		diapason = 10.8;

		if (maxVal <= 9.999847412109375)
		{
			setMode(2);
			diapason = 10.0;

			if (maxVal <= 4.999923706054688)
			{
				setMode(1);
				diapason = 5.0;
			}
		}
		double setY;
		setY = minVal;
		setOffsetY(setY);
	}
	else
	{
		setMode(6);
		diapason = 21.6;

		if (minVal >= -9.999847412109375)
		{
			setMode(5);
			diapason = 20.0;

			if (minVal >= -4.999923706054688)
			{
				setMode(4);
				diapason = 10.0;
			}
		}
		double setY;
		setY = diapason / 2 - Abs(minVal);
		setOffsetY(setY);
	}

	double ampl;
	ampl = Abs(maxVal - minVal);
	setAmplitude(ampl);

	setVal(diapason);
}

//------------------------------------------------------------------------------------------------
// инициализирует массив значений сигнала меандр
void Rectangle::setVal(double diap) {

	uint16_t value;

	// нужно дописать смещение по фазе
	for (int i = 0; i < diskret/2 ; i++)
	{

		value = (amplitude + offsetY) * 0xFFFF / diap;
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