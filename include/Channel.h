#pragma once
#include "C:\Users\Andrey\Desktop\Linearization\Linerization\Working Test\version 1.1\include\signal.h"

class Channel
{
	byte numbChannel;

	uint16_t offsetX;		// начальная фаза (в дискретах)
	uint16_t cycles;		// кол-во циклов
	uint16_t period;		// период сигнала

	byte mode;				// режим работы канала от 1 до 6
							// 1: 0-5V, 2: 0-10V, 3: 0-10.8V, 4: +-5V, 5: +-10V, 6: +-10.8V

	uint16_t val[diskret];	// массив значений сигнала

public:
	Channel(byte);
	~Channel(void);

	uint16_t getPeriod(void) const;
	uint16_t getOffsetX(void) const;
	byte getNumbChannel(void) const;

	void setOffsetX(uint16_t);
	void setVal(Signal&);

	byte getMode(void) const;
	uint16_t getVal(int) const;
};