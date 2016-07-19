#include "C:\Users\Andrey\Desktop\Linerization\Working Test\testDAC\include\Sinus.h"
#include <math.h>


Sinus::Sinus(double _minVal, double _maxVal, double setX)
{
	setParam(_minVal, _maxVal);				// _minVal, _maxVal "������" ������� � �������
	setOffsetX(setX);						// ���������� ��������� ���� (� ��������)
}

Sinus::~Sinus()
{
}

//--------------------------------------------------------

void Sinus::setAmplitude(double ampl) {
	amplitude = ampl;
}

void Sinus::setOffsetY(double setY) {
	offsetY = setY;
}

void Sinus::setOffsetX(double setX) {
	offsetX = (diskret/360.0)*setX;		// ��������� �� �������� � ��������
}

void Sinus::setMode(byte _mode) {
	mode = _mode;
}

double Sinus::getAmplitude(void) const {
	return amplitude;
}

double Sinus::getOffsetY(void) const {
	return offsetY;
}

uint16_t Sinus::getOffsetX(void) const {
	return offsetX;
}

uint16_t Sinus::getVal(int number) const {
	return val[number];
}

byte Sinus::getMode(void) const {
	return mode;
}

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
// ������������ ��������� � �������� �����. ��� OY
// minVal � maxVal ������ "������" ������� � �������
void Sinus::setParam(double minVal, double maxVal) {

	if (minVal < -10.79967041015625) minVal = -10.79967041015625;
	if (maxVal > 10.79967041015625) maxVal = 10.79967041015625;


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
	ampl = Abs(maxVal - minVal) / 2;
	setAmplitude(ampl);

	setVal(diapason);
}

//------------------------------------------------------------------------------------------------
// �������������� ������ �������� ������� sin(x)
void Sinus::setVal(double diap) {

	double rad;
	uint16_t value;

	rad = 2 * PI / diskret;

	for (int i = 0; i<diskret; i++)
	{

		value = (amplitude*(sin(i * rad) + 1) + offsetY) * 0xFFFF / diap;
		if (value>0xFFFF) value = 0xFFFF;
		if (value<0x0) value = 0x0;

		val[i] = value & 0xFFFF;

	}
}
