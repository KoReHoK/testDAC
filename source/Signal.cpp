#include "C:\Users\Andrey\Desktop\Linerization\Working Test\testDAC\include\Signal.h"


Signal::Signal(void)
{
}

Signal::~Signal(void)
{
}


//--------------------------------------------------------

void Signal::setOffsetY(float _setY) {
	offsetY = _setY;
}

void Signal::setOffsetX(float _setX) {
	if (_setX < 0.0) _setX = 0.0;
	if (_setX > 360.0) _setX = 360.0;
	offsetX = (diskret / 360.0)*_setX;		// ��������� �� �������� � ��������
}

void Signal::setCycles(uint16_t _cycles)
{
	if (_cycles < 0) _cycles = 0;
	cycles = _cycles;
}

void Signal::setFrequence(uint16_t _freq)
{
	if (_freq < 0) _freq = 0;
	if (_freq > 10000) _freq = 10000;
	frequence = _freq;
}

void Signal::setMode(byte _mode) {
	mode = _mode;
}

float Signal::getAmplitude(void) const {
	return float(amplitude);
}

float Signal::getOffsetY(void) const {
	return float(offsetY);
}

uint16_t Signal::getOffsetX(void) const {
	return uint16_t(offsetX);
}

uint16_t Signal::getCycles(void) const
{
	return uint16_t(cycles);
}

uint16_t Signal::getFrequence(void) const
{
	return uint16_t(frequence);
}

uint16_t Signal::getVal(int _number) const {
	return uint16_t(val[_number]);
}

byte Signal::getMode(void) const {
	return byte(mode);
}

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
// ������������ ��������� � �������� �����. ��� OY
// minVal � maxVal ������ "������" ������� � �������
void Signal::setParam(float _minVal, float _maxVal) {

	if (_minVal < -10.79967041015625) _minVal = -10.79967041015625;
	if (_maxVal > 10.79967041015625) _maxVal = 10.79967041015625;


	double diapason;	// 1: 0-5V, 2: 0-10V, 3: 0-10.8V, 4: +-5V, 5: +-10V, 6: +-10.8V
	if (_minVal >= 0.0)
	{
		setMode(3);
		diapason = 10.8;

		if (_maxVal <= 9.999847412109375)
		{
			setMode(2);
			diapason = 10.0;

			if (_maxVal <= 4.999923706054688)
			{
				setMode(1);
				diapason = 5.0;
			}
		}
		double setY;
		setY = _minVal;
		setOffsetY(setY);
	}
	else
	{
		setMode(6);
		diapason = 21.6;

		if (_minVal >= -9.999847412109375)
		{
			setMode(5);
			diapason = 20.0;

			if (_minVal >= -4.999923706054688)
			{
				setMode(4);
				diapason = 10.0;
			}
		}
		double setY;
		setY = diapason / 2 - Abs(_minVal);
		setOffsetY(setY);
	}

	double ampl;
	ampl = Abs(_maxVal - _minVal) / 2;
	setAmplitude(ampl);

	setVal(diapason);
}