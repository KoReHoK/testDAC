#pragma once
#define PI 3.14159265		// число ПИ
#define diskret 100			// кол-во отсчетов сигнала
#include "Arduino.h"

class Signal
{
protected:
	
	float amplitude;		// амплитуда сигнала
	float offsetY;			// смещение относительно оси OY
	uint16_t offsetX;		// начальная фаза (в дискретах)
	uint16_t cycles;		// кол-во циклов
	uint16_t frequence;		// частота сигнала

	uint16_t val[diskret];	// массив значений сигнала

	byte mode;				// режим работы ЦАПа от 1 до 6
							// 1: 0-5V, 2: 0-10V, 3: 0-10.8V, 4: +-5V, 5: +-10V, 6: +-10.8V
public:
	Signal(void);
	~Signal(void);
	
	virtual void setAmplitude(float) = 0;	// для каждого вида сигнала по своему высчитывается амплитуда
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

