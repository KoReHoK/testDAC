#include "C:\Users\Andrey\Desktop\Linearization\Linerization\Working Test\version 1.1\include\DAC.h"

Signal* sign;

DAC::DAC()
{
}


DAC::~DAC()
{
}

void DAC::setDAC(uint16_t DACValue, Canal_ID DACNumber) { //CHECKED OK

	unsigned long DACAddress;
	unsigned long data;	//data is the voltage requested from the user application


	switch (DACNumber) {

	case canalA:

		DACAddress = 0x00000;
		data = DACAddress | channel_A.getVal(DACValue);		// val[DACValue];

		break;

	case canalB:

		DACAddress = 0x10000;
		data = DACAddress | channel_B.getVal(DACValue);

		break;

	case canalC:

		DACAddress = 0x20000;
		data = DACAddress | channel_C.getVal(DACValue);

		break;

	case canalD:

		DACAddress = 0x30000;
		data = DACAddress | channel_D.getVal(DACValue);

		break;

	}

	sendData(data);

	loadDACs();

}

void DAC::loadDACs(void) { //CHECKED OK

	unsigned long data = 0x1D0000;

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

uint16_t DAC::getOffsetX(Canal_ID _id) const
{
	switch (_id) {
	case canalA: return uint16_t(channel_A.getOffsetX()); break;
	case canalB: return uint16_t(channel_B.getOffsetX()); break;
	case canalC: return uint16_t(channel_C.getOffsetX()); break;
	case canalD: return uint16_t(channel_D.getOffsetX()); break;
	}
	
}

void DAC::setOffsetX(uint16_t _val, Canal_ID _id)
{
	switch (_id) {
	case canalA: channel_A.setOffsetX(_val); break;
	case canalB: channel_B.setOffsetX(_val); break;
	case canalC: channel_C.setOffsetX(_val); break;
	case canalD: channel_D.setOffsetX(_val); break;
	}
}

void DAC::configDAC(Canal_ID _id)
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

	switch (_id) {

	case canalD:

		switch (channel_D.getMode()) {

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

	case canalC:

		switch (channel_C.getMode()) {

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

	case canalB:

		switch (channel_B.getMode()) {

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

	case canalA:

		switch (channel_A.getMode()) {

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

void DAC::setVal(Signal& _sign, Canal_ID _id)
{
	switch (_id)
	{
		case canalA: channel_A.setVal(_sign); break;
		case canalB: channel_B.setVal(_sign); break;
		case canalC: channel_C.setVal(_sign); break;
		case canalD: channel_D.setVal(_sign); break;
	}
		
}





void DAC::start(void) { //CHECKED OK

	sendData(0x10000F); //Send B000100000000000000001111 power up all DACs

	Timer0.start(channel_A.getPeriod());
	Timer1.start(channel_B.getPeriod());
	Timer2.start(channel_C.getPeriod());
	Timer3.start(channel_D.getPeriod());
}

void DAC::stop(void){

	Timer0.stop();
	Timer1.stop();
	Timer2.stop();
	Timer3.stop();

	sendData(0x100000); //Send B000100000000000000000000 power down all DACs
}

void DAC::config(Signal_ID sign_id, Canal_ID canal_id, float _minValue, float _maxValue, float _offSetX, uint16_t _frequence, uint16_t _kolCycles, uint16_t _symmetry) {

	switch (canal_id) {
	case canalA:
	{

		sign = Signal::createSignal(sign_id);
		sign->setParam(_minValue, _maxValue, _offSetX, _frequence, _kolCycles, _symmetry);
		setVal(*sign, canalA);

		configDAC(canalA); //Must configure before turning the DACs on

//		Timer0.attachInterrupt(interFuncA);

	}break;

	case canalB:
	{

		sign = Signal::createSignal(sign_id);
		sign->setParam(_minValue, _maxValue, _offSetX, _frequence, _kolCycles, _symmetry);
		setVal(*sign, canalB);

		configDAC(canalB); //Must configure before turning the DACs on

//		Timer1.attachInterrupt(interFuncB);

	}break;

	case canalC:
	{

		sign = Signal::createSignal(sign_id);
		sign->setParam(_minValue, _maxValue, _offSetX, _frequence, _kolCycles, _symmetry);
		setVal(*sign, canalC);

		configDAC(canalC); //Must configure before turning the DACs on

//		Timer2.attachInterrupt(interFuncC);

	}break;

	case canalD:
	{

		sign = Signal::createSignal(sign_id);
		sign->setParam(_minValue, _maxValue, _offSetX, _frequence, _kolCycles, _symmetry);
		setVal(*sign, canalD);

		configDAC(canalD); //Must configure before turning the DACs on

//		Timer3.attachInterrupt(interFuncD);

	}break;
	}

}