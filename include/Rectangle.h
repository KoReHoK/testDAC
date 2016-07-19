#pragma once
#include "c:\users\andrey\desktop\linerization\working test\testdac\include\signal.h"
class Rectangle :
	public Signal
{
public:

	Rectangle(double, double, double);	// _minVal, _maxVal, OffsetX

	~Rectangle(void);

	void setAmplitude(double);
	void setOffsetY(double);
	void setOffsetX(double);

	double getAmplitude(void) const;
	double getOffsetY(void) const;
	uint16_t getOffsetX(void) const;

	void setVal(double);
	uint16_t getVal(int) const;

	void setParam(double, double);

	void setMode(byte);
	byte getMode(void) const;

};

