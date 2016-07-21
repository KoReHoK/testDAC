#include <SPI.h>
#include "C:\Users\Andrey\Desktop\Linerization\Working Test\testDAC\include\DAC.h"
#include "C:\Users\Andrey\Desktop\Linerization\Working Test\testDAC\include\Sinus.h"
#include "C:\Users\Andrey\Desktop\Linerization\Working Test\testDAC\include\Rectangle.h"
#include "C:\Users\Andrey\Desktop\Linerization\Working Test\testDAC\include\Triangle.h"


#define minValue 0.0		// value in volts
#define maxValue 7.0
#define offSetX 0.0			// value in degrees (нужно добавить проверку)
#define frequnce 100		// real frequency signal generation is obtained if frequnce*diskret in mks  
#define kolCycles 0			// 0 - сcontinium mode
#define symmetr 80			// for rectangle and triangle


//Sinus sinus(minValue, maxValue, offSetX, frequnce, kolCycles);
//Rectangle rectangle(minValue, maxValue, offSetX, frequnce, kolCycles, symmetr);									
Triangle triangle(minValue, maxValue, offSetX, frequnce, kolCycles, symmetr);

//uint16_t count = sinus.getOffsetX();		// задает начальную фазу сигнала
//byte voltage = sinus.getMode();			// selects the signal generation mode from 1 to 6

//uint16_t count = rectangle.getOffsetX();
//byte voltage = rectangle.getMode();


//---------------------------------------------
DAC dacA(triangle, 1);
DAC dacB(triangle, 2);
DAC dacC(triangle, 3);
DAC dacD(triangle, 4);


void setup() {

	// see SPI settings!!!!!!!!!!!
	pinMode(sspin, OUTPUT);
	SPI.begin();
	SPI.setBitOrder(MSBFIRST);
	SPI.setDataMode(SPI_MODE2);
	SPI.setClockDivider(5);

	DAC::ConfigDACs(DACQTY); //Must configure before turning the DACs on
	DAC::PowerDACs(DACQTY);  //Power up the number of requested DACs

	Timer1.attachInterrupt(dacA.start);
	Timer1.start(dacA.getFrequence());				

}

// the loop function runs over and over again until power down or reset
void loop() {
	
}