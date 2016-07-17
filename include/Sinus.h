#pragma once
#include "signal.h"
class Sinus : 
	public Signal
{
public:

	Sinus();
	Sinus(double, double);
	Sinus(double, double, double);	// _minVal, _maxVal, OffsetX

	~Sinus(void);

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

