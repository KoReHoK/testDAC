#include <SPI.h>
#include "C:\Users\Andrey\Desktop\Linearization\Linerization\Working Test\version 1.1\include\DAC.h"

#define minValue 0.0		// value in volts
#define maxValue 10.0
#define offSetX 0.0			// value in degrees (нужно добавить проверку)
#define define_period 100	// real period signal generation is obtained if period*diskret in mks  
#define kolCycles 0			// 0 - сcontinium mode
#define symmetr 100			// for rectangle and triangle

bool flag = true;			// прерывание на прием данных

//---------------------------------------------------------------------
//----------------- DACs initialize -----------------------------------

DAC dac;

//----------------- End DACs initialize--------------------------------
//---------------------------------------------------------------------

void setup() {

	// see SPI settings!!!!!!!!!!!
	pinMode(sspin, OUTPUT);
	SPI.begin();
	SPI.setBitOrder(MSBFIRST);
	SPI.setDataMode(SPI_MODE2);
	SPI.setClockDivider(5);

	Timer0.attachInterrupt(interFuncA);
	Timer1.attachInterrupt(interFuncB);
	Timer2.attachInterrupt(interFuncC);
	Timer3.attachInterrupt(interFuncD);
}

// the loop function runs over and over again until power down or reset
void loop() {

	if (flag == true){

		dac.stop();
		dac.config(Sinus_ID, canalA, minValue, maxValue, offSetX, define_period, kolCycles, symmetr);
		dac.start();
		flag = false;
	}

}

//-------------- interruptFuncs -----------------------
//-----------------------------------------------------

void interFuncA(void) {

	uint16_t count = dac.getOffsetX(canalA);

	if (count >= diskret) count = 0;
	dac.setDAC(count, canalA);
	dac.setOffsetX(++count, canalA);
}

void interFuncB(void) {

	uint16_t count = dac.getOffsetX(canalB);

	if (count >= diskret) count = 0;
	dac.setDAC(count, canalB);
	dac.setOffsetX(++count, canalB);
}

void interFuncC(void) {

	uint16_t count = dac.getOffsetX(canalC);

	if (count >= diskret) count = 0;
	dac.setDAC(count, canalC);
	dac.setOffsetX(++count, canalC);
}

void interFuncD(void) {

	uint16_t count = dac.getOffsetX(canalD);

	if (count >= diskret) count = 0;
	dac.setDAC(count, canalD);
	dac.setOffsetX(++count, canalD);
}

//---------- End interrupts funcs -------------------
//---------------------------------------------------