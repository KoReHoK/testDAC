#pragma once
#include "Arduino.h"
#include <SPI.h>
#include "C:\Users\Andrey\Desktop\Linearization\Linerization\Working Test\version 1.1\include\Channel.h"
#include "C:\Users\Andrey\Desktop\Linearization\Linerization\Working Test\version 1.1\include\DueTimer.h"

#define sspin 10			// pin Slave Select on Arduino

enum Canal_ID {canalA = 0, canalB, canalC, canalD};


class DAC
{
private:
	
	Channel channel_A{ canalA };
	Channel channel_B{ canalB };
	Channel channel_C{ canalC };
	Channel channel_D{ canalD };

	void loadDACs(void);
	void configDAC(Canal_ID);
	//void setDAC(uint16_t, Canal_ID);
	void setVal(Signal&, Canal_ID);

	//static void interFuncA(void);
	//static void interFuncB(void);
	//static void interFuncC(void);
	//static void interFuncD(void);
	
	static void sendData(long);

	//uint16_t getOffsetX(Canal_ID) const;
	//void setOffsetX(uint16_t, Canal_ID);

public:
	DAC();
	~DAC();

	void start(void);
	void stop(void);
	void config(Signal_ID, Canal_ID, float, float, float, uint16_t, uint16_t, uint16_t);

	void setDAC(uint16_t, Canal_ID);
	uint16_t getOffsetX(Canal_ID) const;
	void setOffsetX(uint16_t, Canal_ID);
};