#pragma once
#define diskret 100			// ���-�� �������� �������
#include "Arduino.h"
#include <assert.h>

enum Signal_ID { Sinus_ID = 0, Triangle_ID, Rectangle_ID };

class Signal
{
protected:
	
	float amplitude;		// ��������� �������
	float offsetY;			// �������� ������������ ��� OY
	uint16_t offsetX;		// ��������� ���� (� ���������)
	uint16_t cycles;		// ���-�� ������
	uint16_t period;		// ������� �������
	uint16_t symmetry;		// ��������� ������� (��� sin 100% const)

	uint16_t val[diskret];	// ������ �������� �������

	byte mode;				// ����� ������ ���� �� 1 �� 6
							// 1: 0-5V, 2: 0-10V, 3: 0-10.8V, 4: +-5V, 5: +-10V, 6: +-10.8V
public:
	Signal(void);
	~Signal(void);
	
	void setAmplitude(float);	
	void setOffsetY(float);
	void setOffsetX(float);
	void setCycles(uint16_t);
	void setPeriod(uint16_t);
	void setSymmetry(uint16_t);

	float getAmplitude(void) const;
	float getOffsetY(void) const;
	uint16_t getOffsetX(void) const;
	uint16_t getCycles(void) const;
	uint16_t getPeriod(void) const;
	uint16_t getSymmetry(void) const;

	virtual void setVal(float) = 0;		// ��� ������� ���� ������� �� ������ ������������� ������ ��������
	uint16_t getVal(int) const;

	void setParam(float _minVal, float _maxVal, float _setX, uint16_t _freq, uint16_t _cycles, int _symmetry);

	void setMode(byte);
	byte getMode(void) const;

	static Signal* createSignal(Signal_ID);
};