#include "C:\Users\Andrey\Desktop\Linearization\Linerization\Working Test\version 1.1\include\DAC.h"



DAC::DAC(byte _numbCanal): numbCanal(_numbCanal)
{
	for (int i = 0; i < diskret; i++)
		val[i] = 0x0;
}


DAC::~DAC()
{
}

uint16_t DAC::getFrequence(void)
{
	return uint16_t(frequence);
}

uint16_t DAC::getOffsetX(void)
{
	return uint16_t(offsetX);
}

byte DAC::getNumbCanal(void)
{
	return byte(numbCanal);
}

void DAC::config(void)
{
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
	sendData(config);

	unsigned long output;

	switch (numbCanal) {

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
		switch (mode) {

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

		sendData(output); break;

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
		switch (mode) {

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

		sendData(output); break;

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
		switch (mode) {

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

		sendData(output); break;

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

		switch (mode) {

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

		sendData(output); break;

	}
}

void DAC::powerUpDACs(void) { //CHECKED OK

	sendData(0x10000F); //Send B000100000000000000001111 to initialize 4 DACs
}

void DAC::powerDownDACs(void){

	sendData(0x100000); //Send B000100000000000000000000
}

void DAC::setDAC(int DACValue, byte DACNumber) { //CHECKED OK

	unsigned long DACAddress;
	unsigned long data;	//data is the voltage requested from the user application


	switch (DACNumber) {

	case 1:

		DACAddress = 0x00000;
		data = DACAddress | val[DACValue];

		break;

	case 2:

		DACAddress = 0x10000;
		data = DACAddress | val[DACValue];

		break;

	case 3:

		DACAddress = 0x20000;
		data = DACAddress | val[DACValue];

		break;

	case 4:

		DACAddress = 0x30000;
		data = DACAddress | val[DACValue];

		break;

	}

	sendData(data);

	loadDACs();

}

void DAC::setOffsetX(uint16_t _offsetX)
{
	offsetX = _offsetX;
}

void DAC::setVal(Signal &sign)
{
	offsetX = sign.getOffsetX();
	cycles = sign.getCycles();
	frequence = sign.getFrequence();
	mode = sign.getMode();

	for (int i = 0; i < diskret; i++)
		val[i] = sign.getVal(i);
}

void DAC::loadDACs(void) { //CHECKED OK

	unsigned long data = 0x1D0000;

	sendData(data);
}
void DAC::clearDACs(void) { //CHECKED OK

	unsigned long data = 0x1C0000;

	sendData(data);

}

void DAC::sendData(long data) { //CHECKED OK

	digitalWrite(sspin, LOW);

	unsigned char *p = (unsigned char*)&data;

	for (int i = 2; i >= 0; i--) { //MSB first

		SPI.transfer(p[i]);

	}

	digitalWrite(sspin, HIGH);

}