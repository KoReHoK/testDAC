#pragma once
#define PI 3.14159265		// ����� ��
#define diskret 200			// ���-�� �������� �������
#include "Arduino.h"

class Signal
{
protected:
	
	double amplitude;		// ��������� �������
	double offsetY;			// �������� ������������ ��� OY
	uint16_t offsetX;		// ��������� ���� (� ���������)

	uint16_t val[diskret];	// ������ �������� �������

	byte mode;				// ����� ������ ���� �� 1 �� 6
							// 1: 0-5V, 2: 0-10V, 3: 0-10.8V, 4: +-5V, 5: +-10V, 6: +-10.8V
public:
	Signal(void);
	~Signal(void);
	
	virtual void setAmplitude(double) = 0;
	virtual void setOffsetY(double) = 0;
	virtual void setOffsetX(double) = 0;

	virtual double getAmplitude(void) const = 0;
	virtual double getOffsetY(void) const = 0;
	virtual uint16_t getOffsetX(void) const = 0;

	virtual void setVal(double) = 0;
	virtual uint16_t getVal(int) const = 0;

	virtual void setParam(double, double) = 0;

	virtual void setMode(byte) = 0;
	virtual byte getMode(void) const = 0;

};

