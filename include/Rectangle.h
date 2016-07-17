#pragma once
#include "c:\users\andrey\desktop\linerization\working test\testdac\include\signal.h"
class Rectangle :
	public Signal
{
public:

	Rectangle(void);
	~Rectangle(void);
	uint16_t getVal(int number) const;

};

