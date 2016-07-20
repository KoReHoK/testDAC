#pragma once
#define PI 3.14159265		// ����� ��
#define diskret 100			// ���-�� �������� �������
#include "Arduino.h"

class Signal
{
protected:
	
	float amplitude;		// ��������� �������
	float offsetY;			// �������� ������������ ��� OY
	uint16_t offsetX;		// ��������� ���� (� ���������)
	uint16_t cycles;		// ���-�� ������
	uint16_t frequence;		// ������� �������

	uint16_t val[diskret];	// ������ �������� �������

	byte mode;				// ����� ������ ���� �� 1 �� 6
							// 1: 0-5V, 2: 0-10V, 3: 0-10.8V, 4: +-5V, 5: +-10V, 6: +-10.8V
public:
	Signal(void);
	~Signal(void);
	
	virtual void setAmplitude(float) = 0;	// ��� ������� ���� ������� �� ������ ������������� ���������
	void setOffsetY(float);
	void setOffsetX(float);
	void setCycles(uint16_t);
	void setFrequence(uint16_t);

	float getAmplitude(void) const;
	float getOffsetY(void) const;
	uint16_t getOffsetX(void) const;
	uint16_t getCycles(void) const;
	uint16_t getFrequence(void) const;

	virtual void setVal(float) = 0;
	uint16_t getVal(int) const;

	void setParam(float, float);

	void setMode(byte);
	byte getMode(void) const;

};

