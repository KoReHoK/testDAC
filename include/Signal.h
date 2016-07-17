#pragma once
#define diskret 100		// ���-�� �������� �������
#include "Arduino.h"

class Signal
{
protected:
	
	uint16_t amplitude;		// ��������� �������
	uint16_t offsetY;		// �������� ������������ ��� OY
	double offsetX;			// ��������� ���� (� ��������)

	uint16_t val[diskret];	// ������ �������� �������

	byte mode;				// ����� ������ ���� �� 1 �� 6
							// 1: 0-5V, 2: 0-10V, 3: 0-10.8V, 4: +-5V, 5: +-10V, 6: +-10.8V
public:
	Signal(void);
	~Signal(void);
	
	virtual void setAmplitude(uint16_t) = 0;
	virtual void setOffsetY(uint16_t) = 0;
	virtual void setOffsetX(double) = 0;

	virtual uint16_t getAmplitude(void) const = 0;
	virtual uint16_t getOffsetY(void) const = 0;
	virtual uint16_t getOffsetX(void) const = 0;

	virtual void setVal(void) = 0;
	virtual uint16_t getVal(int) const = 0;

	virtual void setParam(double, double) = 0;

	virtual void setMode(byte) = 0;
	virtual byte getMode(void) const = 0;

};

