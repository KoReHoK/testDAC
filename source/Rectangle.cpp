#include "c:\users\andrey\desktop\linerization\working test\testdac\include\Rectangle.h"


Rectangle::Rectangle(void)
{
	setParam(0.0, 5.0);		// _minVal, _maxVal в вольтах
	setOffsetX(0.0);		// выставляет начальную фазу (в градусах)
	setVal();				// рассчитывает значения массива сигнала
}

Rectangle::Rectangle(double _minVal, double _maxVal)
{
	setParam(_minVal, _maxVal);
	setOffsetX(0.0);
	setVal();
}

Rectangle::Rectangle(double _minVal, double _maxVal, double setX)
{
	setParam(_minVal, _maxVal);
	setOffsetX(setX);
	setVal();
}

Rectangle::~Rectangle(void)
{
}

//--------------------------------------------------------

void Rectangle::setAmplitude(uint16_t ampl) {
	amplitude = ampl;
}

void Rectangle::setOffsetY(uint16_t setY) {
	offsetY = setY;
}

void Rectangle::setOffsetX(double setX) {
	offsetX = setX;
}

void Rectangle::setMode(byte _mode) {
	mode = _mode;
}

uint16_t Rectangle::getAmplitude(void) const {
	return amplitude;
}

uint16_t Rectangle::getOffsetY(void) const {
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

	double absMax;
	if (Abs(minVal) > Abs(maxVal))
		absMax = minVal;
	else
		absMax = maxVal;

	double diapason;	// 1: 0-5V, 2: 0-10V, 3: 0-10.8V, 4: +-5V, 5: +-10V, 6: +-10.8V
	if (absMax >= 0.0)
	{
		setMode(3);
		diapason = 10.8;

		if (absMax <= 10.0)
		{
			setMode(2);
			diapason = 10.0;

			if (absMax <= 5.0)
			{
				setMode(1);
				diapason = 5.0;
			}
		}
	}
	else
	{
		setMode(6);
		diapason = 21.6;

		if (absMax >= -10.0)
		{
			setMode(5);
			diapason = 20.0;

			if (absMax >= -5.0)
			{
				setMode(4);
				diapason = 10.0;
			}
		}
	}


	uint16_t ampl;
	ampl = Abs(maxVal - minVal) * 0x8000 / diapason;
	setAmplitude(ampl);

	uint16_t setY;
	setY = maxVal * 0x8000 / diapason - ampl;
	setOffsetY(setY);
}

//------------------------------------------------------------------------------------------------
// инициализирует массив значений сигнала меандр
void Rectangle::setVal(void) {

	uint16_t value;

	// нужно дописать смещение по фазе
	for (int i = 0; i < diskret/2 ; i++)
	{

		// нужно подумать над проверкой
		value = amplitude + offsetY;
		if (value>0xFFFF) value = 0xFFFF;
		if (value<0x0) value = 0x0;

		val[i] = value & 0xFFFF;

	}

	for (int i = diskret / 2; i < diskret; i++)
	{

		// нужно подумать над проверкой
		value = offsetY - amplitude;
		if (value>0xFFFF) value = 0xFFFF;
		if (value<0x0) value = 0x0;

		val[i] = value & 0xFFFF;

	}
}