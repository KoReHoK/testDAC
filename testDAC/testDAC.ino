#include <SPI.h>
#include "C:\Users\Andrey\Desktop\Linearization\Linerization\Working Test\version 1.1\include\DueTimer.h"
#include "C:\Users\Andrey\Desktop\Linearization\Linerization\Working Test\version 1.1\include\DAC.h"
#include "C:\Users\Andrey\Desktop\Linearization\Linerization\Working Test\version 1.1\include\Sinus.h"
#include "C:\Users\Andrey\Desktop\Linearization\Linerization\Working Test\version 1.1\include\Rectangle.h"
#include "C:\Users\Andrey\Desktop\Linearization\Linerization\Working Test\version 1.1\include\Triangle.h"

#define numbSign 1			// 1 - sinus, 2 - triangle, 3 - rectangle
#define numbDAC 1			// 1 - dacA, 2 - dacB, 3 - dacC, 4 - dacD

#define minValue 0.0		// value in volts
#define maxValue 0.0
#define offSetX 0.0			// value in degrees (нужно добавить проверку)
#define period 100			// real period signal generation is obtained if period*diskret in mks  
#define kolCycles 0			// 0 - сcontinium mode
#define symmetr 100			// for rectangle and triangle


Sinus sinus;							
Triangle triangle;
Rectangle rectangle;


Rectangle nullSignal;		// нулевой сигнал (для откл. какого-либо канала)

//---------------------------------------------------------------------
//----------------- DACs initialize -----------------------------------

DAC dacA(1);
DAC dacB(2);
DAC dacC(3);
DAC dacD(4);

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
	Timer0.start(dacA.getFrequence());

	Timer1.attachInterrupt(interFuncB);
	Timer1.start(dacB.getFrequence());

	Timer2.attachInterrupt(interFuncC);
	Timer2.start(dacC.getFrequence());

	Timer3.attachInterrupt(interFuncD);
	Timer3.start(dacD.getFrequence());
}

// the loop function runs over and over again until power down or reset
void loop() {
	funcSwitch(numbSign, numbDAC, minValue, maxValue, offSetX, period, kolCycles, symmetr);
}


//-------------- interruptFuncs -----------------------
//-----------------------------------------------------

void interFuncA(void) {

	uint16_t count = dacA.getOffsetX();
	byte numbCanal = dacA.getNumbCanal();

	if (count >= diskret) count = 0;
	dacA.setDAC(count, numbCanal);
	dacA.setOffsetX(++count);
}

void interFuncB(void) {

	uint16_t count = dacB.getOffsetX();
	byte numbCanal = dacB.getNumbCanal();

	if (count >= diskret) count = 0;
	dacB.setDAC(count, numbCanal);
	dacB.setOffsetX(++count);
}

void interFuncC(void) {

	uint16_t count = dacC.getOffsetX();
	byte numbCanal = dacC.getNumbCanal();

	if (count >= diskret) count = 0;
	dacC.setDAC(count, numbCanal);
	dacC.setOffsetX(++count);
}

void interFuncD(void) {

	uint16_t count = dacD.getOffsetX();
	byte numbCanal = dacD.getNumbCanal();

	if (count >= diskret) count = 0;
	dacD.setDAC(count, numbCanal);
	dacD.setOffsetX(++count);
}

//---------- End interrupts funcs -------------------
//---------------------------------------------------


//------------ Begin funcSwitch ---------------------
//---------------------------------------------------

void funcSwitch(int _numbSign, int _numbDAC, float _minValue, float _maxValue, float _offSetX, uint16_t _frequence, uint16_t _kolCycles, int _symmetry) {

	DAC::powerDownDACs();

	switch (_numbDAC) {
		case 1:	// dacA
			switch (_numbSign) {

				case 1: 
				{
					sinus.setParam(_minValue, _maxValue, _offSetX, _frequence, _kolCycles, _symmetry);
					dacA.setVal(sinus);
				}break;

				case 2:
				{
					triangle.setParam(_minValue, _maxValue, _offSetX, _frequence, _kolCycles, _symmetry);
					dacA.setVal(triangle);
				}break;

				case 3:
				{
					rectangle.setParam(_minValue, _maxValue, _offSetX, _frequence, _kolCycles, _symmetry);
					dacA.setVal(rectangle);
				}break;

			}break;

		case 2: // dacB
			switch (_numbSign) {

				case 1:
				{
					sinus.setParam(_minValue, _maxValue, _offSetX, _frequence, _kolCycles, _symmetry);
					dacB.setVal(sinus);
				}break;

				case 2:
				{
					triangle.setParam(_minValue, _maxValue, _offSetX, _frequence, _kolCycles, _symmetry);
					dacB.setVal(triangle);
				}break;

				case 3:
				{
					rectangle.setParam(_minValue, _maxValue, _offSetX, _frequence, _kolCycles, _symmetry);
					dacB.setVal(rectangle);
				}break;

			}break;

		case 3: // dacC
			switch (_numbSign) {

				case 1:
				{
					sinus.setParam(_minValue, _maxValue, _offSetX, _frequence, _kolCycles, _symmetry);
					dacC.setVal(sinus);
				}break;

				case 2:
				{
					triangle.setParam(_minValue, _maxValue, _offSetX, _frequence, _kolCycles, _symmetry);
					dacC.setVal(triangle);
				}break;

				case 3:
				{
					rectangle.setParam(_minValue, _maxValue, _offSetX, _frequence, _kolCycles, _symmetry);
					dacC.setVal(rectangle);
				}break;

			}break;

		case 4: // dacD
			switch (_numbSign) {

				case 1:
				{
					sinus.setParam(_minValue, _maxValue, _offSetX, _frequence, _kolCycles, _symmetry);
					dacA.setVal(sinus);
				}break;

				case 2:
				{
					triangle.setParam(_minValue, _maxValue, _offSetX, _frequence, _kolCycles, _symmetry);
					dacA.setVal(triangle);
				}break;

				case 3:
				{
					rectangle.setParam(_minValue, _maxValue, _offSetX, _frequence, _kolCycles, _symmetry);
					dacA.setVal(rectangle);
				}break;

			}break;
	}

	dacA.config(); //Must configure before turning the DACs on
	dacB.config();
	dacC.config();
	dacD.config();
		
	DAC::powerUpDACs();
}

//------------ End funcSwitch -----------------------
//---------------------------------------------------