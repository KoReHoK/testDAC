#include "Arduino.h"
#include <SPI.h>
#include "C:\Users\Andrey\Desktop\Linearization\Linerization\Working Test\version 1.1\include\signal.h"
#include "C:\Users\Andrey\Desktop\Linearization\Linerization\Working Test\version 1.1\include\DueTimer.h"

#define sspin 10			// pin Slave Select on Arduino

#pragma once
class DAC
{
private:
	byte numbCanal;
	
	uint16_t offsetX;		// ��������� ���� (� ���������)
	uint16_t cycles;		// ���-�� ������
	uint16_t frequence;		// ������� �������

	uint16_t val[diskret];	// ������ �������� �������

	byte mode;				// ����� ������ ���� �� 1 �� 6
							// 1: 0-5V, 2: 0-10V, 3: 0-10.8V, 4: +-5V, 5: +-10V, 6: +-10.8V
	void loadDACs(void);
	void clearDACs(void);
	
	static void sendData(long);

public:
	DAC(byte);
	~DAC();

	void setDAC(int, byte);
	void setOffsetX(uint16_t);
	void setVal(Signal&);

	uint16_t getFrequence(void);
	uint16_t getOffsetX(void);
	byte getNumbCanal(void);

	void config(void);
	static void powerUpDACs(void);
	static void powerDownDACs(void);
};

