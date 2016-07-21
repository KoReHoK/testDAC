#include "C:\Users\Andrey\Desktop\Linerization\Working Test\testDAC\include\DAC.h"



DAC::DAC(Signal &sign, byte _numbCanal): numbCanal(_numbCanal)
{
	offsetX = sign.getOffsetX();
	cycles = sign.getCycles();
	frequence = sign.getFrequence();
	mode = sign.getMode();

	for (int i = 0; i < diskret; i++)
		val[i] = sign.getVal(i);
}


DAC::~DAC()
{
}

byte DAC::getNumbCanal(void)
{
	return byte(numbCanal);
}

uint16_t DAC::getFrequence(void)
{
	return uint16_t(frequence);
}

//--------------------------------------
void DAC::start(void)
{
	if (offsetX >= diskret) offsetX = 0;
	SetDAC(val[offsetX]);
	offsetX++;
}

void DAC::SetDAC(int DACValue) { //CHECKED OK

	unsigned long DACAddress;
	unsigned long data;	//data is the voltage requested from the user application


	switch (numbCanal) {

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

	}

	SendData(data);

	LoadDACs();

}

void DAC::ConfigDACs(int dacqty) { //CHECKED OK

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

		SendData(output);

		break;

	}

}
void DAC::PowerDACs(int dacqty) { //CHECKED OK

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

void DAC::LoadDACs(void) { //CHECKED OK

	unsigned long data = 0x1D0000;

	SendData(data);
}
void DAC::ClearDACs(void) { //CHECKED OK

	unsigned long data = 0x1C0000;

	SendData(data);

}

void DAC::SendData(long data) { //CHECKED OK

	digitalWrite(sspin, LOW);

	unsigned char *p = (unsigned char*)&data;

	for (int i = 2; i >= 0; i--) { //MSB first

		SPI.transfer(p[i]);

	}

	digitalWrite(sspin, HIGH);

}