#include "..\include\Channel.h"

Channel::Channel(byte _numbChannel): numbChannel(_numbChannel)
{
	for (int i = 0; i < diskret; i++)
		val[i] = 0x0;
}

Channel::~Channel(void)
{
}

uint16_t Channel::getPeriod(void) const
{
	return uint16_t(period);
}

uint16_t Channel::getOffsetX(void) const
{
	return uint16_t(offsetX);
}

byte Channel::getNumbChannel(void) const
{
	return byte(numbChannel);
}

byte Channel::getMode(void) const {
	return byte(mode);
}


uint16_t Channel::getVal(int _number) const {
	return uint16_t(val[_number]);
}

void Channel::setOffsetX(uint16_t _offsetX)
{
	offsetX = _offsetX;
}

void Channel::setVal(Signal &sign)
{
	offsetX = sign.getOffsetX();
	cycles = sign.getCycles();
	period = sign.getPeriod();
	mode = sign.getMode();

	for (int i = 0; i < diskret; i++)
		val[i] = sign.getVal(i);
}