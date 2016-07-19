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
	uint16_t cycles;		// ���-�� ������

	uint16_t val[diskret];	// ������ �������� �������

	byte mode;				// ����� ������ ���� �� 1 �� 6
							// 1: 0-5V, 2: 0-10V, 3: 0-10.8V, 4: +-5V, 5: +-10V, 6: +-10.8V
public:
	Signal(void);
	~Signal(void);
	
	void setAmplitude(double);
	void setOffsetY(double);
	void setOffsetX(double);
	void setCycles(uint16_t);

	double getAmplitude(void) const;
	double getOffsetY(void) const;
	uint16_t getOffsetX(void) const;
	uint16_t getCycles(void) const;

	virtual void setVal(double) = 0;
	uint16_t getVal(int) const;

	void setParam(double, double);

	void setMode(byte);
	byte getMode(void) const;

};

