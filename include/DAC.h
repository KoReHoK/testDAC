#include "Arduino.h"
#include <SPI.h>
#include "C:\Users\Andrey\Desktop\Linerization\Working Test\testDAC\include\signal.h"
#include "C:\Users\Andrey\Desktop\Linerization\Working Test\DueTimer-master\DueTimer.h"

#define sspin 10			// pin Slave Select on Arduino
#define DACQTY 4			// number of active channels from 1 to 4	(��� �������� ������� ����� ��� ������)

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

	void SetDAC(int);
	void SendData(long);
	void LoadDACs(void);
	void ClearDACs(void);

public:
	DAC(Signal&, byte);
	~DAC();

	byte getNumbCanal(void);
	uint16_t getFrequence(void);
	void start(void);
//	void stop(void);

	void ConfigDACs(int);
	void PowerDACs(int);
};

