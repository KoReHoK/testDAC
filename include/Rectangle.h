#pragma once
#include "c:\users\andrey\desktop\linerization\working test\testdac\include\signal.h"
class Rectangle :
	public Signal
{
public:

	Rectangle();
	Rectangle(double, double);
	Rectangle(double, double, double);	// _minVal, _maxVal, OffsetX

	~Rectangle(void);

	void setAmplitude(uint16_t);
	void setOffsetY(uint16_t);
	void setOffsetX(double);

	uint16_t getAmplitude(void) const;
	uint16_t getOffsetY(void) const;
	uint16_t getOffsetX(void) const;

	void setVal(void);
	uint16_t getVal(int) const;

	void setParam(double, double);

	void setMode(byte);
	byte getMode(void) const;

};

