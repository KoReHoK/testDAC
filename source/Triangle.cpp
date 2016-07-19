#include "C:\Users\Andrey\Desktop\Linerization\Working Test\testDAC\include\Triangle.h"


Triangle::Triangle(double _minVal, double _maxVal, double _setX)
{
	setParam(_minVal, _maxVal);				// _minVal, _maxVal "������" ������� � �������
	setOffsetX(_setX);						// ���������� ��������� ���� (� ��������)
}

Triangle::~Triangle()
{
}


//------------------------------------------------------------------------------------------------
// �������������� ������ �������� ������� �����������
void Triangle::setVal(double _diap) {

	uint16_t value;

	for (int i=0; i<diskret; i++)
	{
		
		if (value>0xFFFF) value=0xFFFF;
		if (value<0x0) value=0x0;

		val[i] = value&0xFFFF;

	}
}
