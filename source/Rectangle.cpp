#include "c:\users\andrey\desktop\linerization\working test\testdac\include\Rectangle.h"


Rectangle::Rectangle(void)
{
	uint16_t minVal = 0x0000;
	uint16_t maxVal = 0xFFFF;

	for(int i = 0; i < diskret/2; i++) val[i] = minVal;
	for(int i = diskret/2; i < diskret; i++) val[i] = maxVal;
}


Rectangle::~Rectangle(void)
{
}

uint16_t Rectangle::getVal(int number) const {
	return val[number];
}