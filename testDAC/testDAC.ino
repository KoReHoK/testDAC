#include <SPI.h>
#include "C:\Users\Andrey\Desktop\Linerization\Working Test\DueTimer-master\DueTimer.h"
#include "C:\Users\Andrey\Desktop\Linerization\Working Test\testDAC\include\Sinus.h"
#include "C:\Users\Andrey\Desktop\Linerization\Working Test\testDAC\include\Rectangle.h"

#define DACQTY 1			// number of active channels from 1 to 5 (5 includes all the channels)
#define voltage 1			// selects the signal generation mode from 1 to 6
#define sspin 10			// pin Slave Select on Arduino
#define numberCanal 1		// number of channel output signal from 1 to 4

#define frequnce 1			// real frequency signal generation is obtained if frequnce*diskret in mks  

Sinus sinus;				// generates sine wave signal
//Rectangle rectangle;				
//Saw saw;					
//Triangle triangle;		// implemented as a special case of the saw

volatile int count = 0;		// use volatile for shared variables


void funcStart(void) {

	if (count >= diskret) count = 0;
	SetDAC(sinus.getVal(count), numberCanal);
	count++;

}

void setup() {

	// see SPI settings!!!!!!!!!!!
	pinMode(10, OUTPUT);  
	SPI.begin();
	SPI.setBitOrder(MSBFIRST);
	SPI.setDataMode(SPI_MODE2);
	SPI.setClockDivider(5);

	ConfigDACs(DACQTY); //Must configure before turning the DACs on
	PowerDACs(DACQTY);  //Power up the number of requested DACs

	Timer1.attachInterrupt(funcStart);	
	Timer1.start(frequnce);				

}

// the loop function runs over and over again until power down or reset
void loop() {

}

void ConfigDACs(int dacqty) { //CHECKED OK

							  /*

							  0x180000 = NOP [for readback operations]
							  --------------------------------------------------------
							  OR the following together based on the options desired
							  0x190000 = CTRL Address
							  0x1 = SDO Disable Address
							  0x2 = CLR Select Address
							  0x4 = Clamp Enable Address
							  0x8 = TSD Enable Address
							  ---------------------------------------------------------
							  0x1C0000 = Clear Data Address
							  ---------------------------------------------------------
							  0x1D0000 = Load Data Address
							  ---------------------------------------------------------

							  */
	unsigned long config = 0x190000 | 0x1 | 0x4; //config = CTRL address | SDO Disable | Clamp Enable
	SendData(config);

	unsigned long output;

	switch (dacqty) {

	case 4:

		/*
		---------------------------------------------------------
		Output scale values. Must have overhead supply in order to accomodate
		0xB0000 = 5V
		0xB0001 = 10V
		0xB0002 = 10.8V
		0xB0003 = +-5V
		0xB0004 = +-10V
		0xB0005 = +-10.8V
		---------------------------------------------------------

		*/
		switch (voltage) {

		case 1: //0-5V

			output = 0xB0000;

			break;

		case 2: //0-10V

			output = 0xB0001;

			break;

		case 3: //0-10.8V

			output = 0xB0002;

			break;

		case 4: //+-5V

			output = 0xB0003;

			break;

		case 5: // +-10V

			output = 0xB0004;

			break;

		case 6: //+-10.8V

			output = 0xB0005;

			break;
		}

		SendData(output);

	case 3:

		// fixed typo by Bernd Rilling 12/2013
		// 0x50000 should be 0xA0000
		/*
		---------------------------------------------------------
		Output scale values. Must have overhead supply in order to accomodate
		0xA0000 = 5V
		0xA0001 = 10V
		0xA0002 = 10.8V
		0xA0003 = +-5V
		0xA0004 = +-10V
		0xA0005 = +-10.8V
		---------------------------------------------------------

		*/
		switch (voltage) {

		case 1: //0-5V

			output = 0xA0000;

			break;

		case 2: //0-10V

			output = 0xA0001;

			break;

		case 3: //0-10.8V

			output = 0xA0002;

			break;

		case 4: //+-5V

			output = 0xA0003;

			break;

		case 5: //+-10V

			output = 0xA0004;

			break;

		case 6: //+-10.8V

			output = 0xA0005;

			break;
		}

		SendData(output);

	case 2:

		/*
		---------------------------------------------------------
		Output scale values. Must have overhead supply in order to accomodate
		0x90000 = 5V
		0x90001 = 10V
		0x90002 = 10.8V
		0x90003 = +-5V
		0x90004 = +-10V
		0x90005 = +-10.8V
		---------------------------------------------------------

		*/
		switch (voltage) {

		case 1: //0-5V

			output = 0x90000;

			break;

		case 2: //0-10V

			output = 0x90001;

			break;

		case 3: //0-10.8V

			output = 0x90002;

			break;

		case 4: //+-5V

			output = 0x90003;

			break;

		case 5: //+-10V

			output = 0x90004;

			break;

		case 6: //+-10.8V

			output = 0x90005;

			break;
		}

		SendData(output);

	case 1:

		/*
		---------------------------------------------------------
		Output scale values. Must have overhead supply in order to accomodate
		0x80000 = 5V
		0x80001 = 10V
		0x80002 = 10.8V
		0x80003 = +-5V
		0x80004 = +-10V
		0x80005 = +-10.8V
		---------------------------------------------------------

		*/

		switch (voltage) {

		case 1: //0-5V

			output = 0x80000;

			break;

		case 2: //0-10V

			output = 0x80001;

			break;

		case 3: //0-10.8V

			output = 0x80002;

			break;

		case 4: //+-5V

			output = 0x80003;

			break;

		case 5: //+-10V

			output = 0x80004;

			break;

		case 6: //+-10.8V

			output = 0x80005;

			break;
		}

		SendData(output);

		break;

	}

}

void PowerDACs(int dacqty) { //CHECKED OK

	switch (dacqty) {

	case 1:

		SendData(0x100001); //Send B000100000000000000000001 to initialize only the first DAC

		break;

	case 2:

		SendData(0x100003); //Send B000100000000000000000011 to initialize 2 DACs

		break;

	case 3:

		SendData(0x100007); //Send B000100000000000000000111 to initialize 3 DACs

		break;

	case 4:

		SendData(0x10000F); //Send B000100000000000000001111 to initialize  DACs

		break;
	}
}

void SetDAC(int DACValue, int DACNumber) { //CHECKED OK

	unsigned long DACAddress;
	unsigned long data;	//data is the voltage requested from the user application


	switch (DACNumber) {

	case 1:

		DACAddress = 0x00000;
		data = DACAddress | DACValue;

		break;

	case 2:

		DACAddress = 0x10000;
		data = DACAddress | DACValue;

		break;

	case 3:

		DACAddress = 0x20000;
		data = DACAddress | DACValue;

		break;

	case 4:

		DACAddress = 0x30000;
		data = DACAddress | DACValue;

		break;

	case 5:
		//all dacs
		DACAddress = 0x40000;
		data = DACAddress | DACValue;

	}

	SendData(data);

	LoadDACs();

}


void LoadDACs() { //CHECKED OK

	unsigned long data = 0x1D0000;

	SendData(data);
}
void ClearDACs() { //CHECKED OK

	unsigned long data = 0x1C0000;

	SendData(data);

}

// added by Bernd Rilling 12/2013
void ReadDACsRegister(int DACRegister, int DACNumber, byte raw[]) {

	unsigned long DACAddress;
	unsigned long data;
	unsigned long DACValue;

	/*
	-------------------------------------------------------------------
	DACRegister
	1 = DAC register
	2 = Output range select register
	3 = Power control register
	4 = Control register
	-------------------------------------------------------------------
	*/

	switch (DACNumber) {

	case 1: //DAC A

		DACAddress = 0x00000;

		break;

	case 2: //DAC B

		DACAddress = 0x10000;

		break;

	case 3: //DAC C

		DACAddress = 0x20000;

		break;

	case 4: //DAC D

		DACAddress = 0x30000;

		break;
	}

	switch (DACRegister) {

	case 1:	//DAC register

		DACValue = 0x800000;
		data = DACValue | DACAddress;

		break;

	case 2:	//Output range select register

		DACValue = 0x880000;
		data = DACValue | DACAddress;

		break;

	case 3:	//Power control register
			//DACNumber don't care

		data = 0x900000;

		break;

	case 4:	//Control register
			//DACNumber don't care

		data = 0x990000;

		break;

	}
	//Send read command for the selected register and DACNumber

	SendData(data);

	digitalWrite(sspin, LOW);

	//Send B0001 8000 0000 0000 0000 0000 = NOP
	//Read 3 bytes

	for (int i = 2; i >= 0; i--) {

		raw[i] = SPI.transfer(0x180000);

	}

	digitalWrite(sspin, HIGH);

}
// end added...

void SendData(long data) { //CHECKED OK

	digitalWrite(sspin, LOW);

	unsigned char *p = (unsigned char*)&data;

	for (int i = 2; i >= 0; i--) { //MSB first

		SPI.transfer(p[i]);

	}

	digitalWrite(sspin, HIGH);

}