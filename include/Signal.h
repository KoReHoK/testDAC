#pragma once
#define PI 3.14159265		// число ПИ
#define diskret 200			// кол-во отсчетов сигнала
#include "Arduino.h"

class Signal
{
protected:
	
	double amplitude;		// амплитуда сигнала
	double offsetY;			// смещение относительно оси OY
	uint16_t offsetX;		// начальная фаза (в дискретах)

	uint16_t val[diskret];	// массив значений сигнала

	byte mode;				// режим работы ЦАПа от 1 до 6
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

