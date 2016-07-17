//#include "C:\Users\Andrey\Desktop\Linerization\Working Test\testDAC\include\Sinus.h"
//#include <math.h>
//
//#define PI 3.14159265        // число ПИ
//
//
//Sinus::Sinus()		   
//{     
//	setParam(0.0, 5.0);		// _minVal, _maxVal
//
////	setAmplitude(0x8000);	// выставляет амплитуду сигнала
////	setOffsetY(0x8000);		// выставляет смещение по оси OY
//	setOffsetX(0.0);		// выставляет начальную фазу (в градусах)
//	setVal();				// рассчитывает значения массива сигнала	
//}
//
//Sinus::Sinus(double _minVal, double _maxVal)
//{
//	setParam(_minVal, _maxVal);
//	setOffsetX(0.0);
//	setVal();
//}
//
//Sinus::Sinus(double _minVal, double _maxVal, double setX)
//{
//	setParam(_minVal, _maxVal);
//	setOffsetX(setX);
//	setVal();
//}
//
//Sinus::~Sinus()
//{
//}
//
////--------------------------------------------------------
//
//void Sinus::setAmplitude(uint16_t ampl){
//	amplitude = ampl;
//}
//
//void Sinus::setOffsetY(uint16_t setY){
//	offsetY = setY;
//}
//
//void Sinus::setOffsetX(double setX){
//	offsetX = setX;
//}
//
//void Sinus::setMode(byte _mode) {
//	mode = _mode;
//}
//
//uint16_t Sinus::getAmplitude(void) const {
//	return amplitude;
//}
//
//uint16_t Sinus::getOffsetY(void) const {
//	return offsetY;
//}
//
//uint16_t Sinus::getOffsetX(void) const {
//	return offsetX;
//}
//
//uint16_t Sinus::getVal(int number) const {
//	return val[number];
//}
//
//byte Sinus::getMode(void) const {
//	return mode;
//}
//
////------------------------------------------------------------------------------------------------
////------------------------------------------------------------------------------------------------
//// рассчитывает амплитуду и смещение относ. оси OY
//// minVal и maxVal задают "размах" сигнала в вольтах
//void Sinus::setParam(double minVal, double maxVal) { 
//
//	if(minVal < -10.8) minVal = -10.8;
//	if(maxVal > 10.8) maxVal = 10.8;
//
//	double absMax;
//	if(Abs(minVal) > Abs(maxVal)) 
//		absMax = minVal;
//	else
//		absMax = maxVal;
//
//	double diapason;	// 1: 0-5V, 2: 0-10V, 3: 0-10.8V, 4: +-5V, 5: +-10V, 6: +-10.8V
//	if(absMax >= 0.0)
//	{
//		setMode(3);
//		diapason = 10.8;
//
//		if(absMax <= 10.0)
//		{
//			setMode(2);
//			diapason = 10.0;
//
//			if(absMax <= 5.0)
//			{
//				setMode(1);
//				diapason = 5.0;
//			}
//		}
//	}
//	else
//	{
//		setMode(6);
//		diapason = 21.6;
//
//		if(absMax >= -10.0)
//		{
//			setMode(5);
//			diapason = 20.0;
//
//			if(absMax >= -5.0)
//			{
//				setMode(4);
//				diapason = 10.0;
//			}
//		}
//	}
//
//
//	uint16_t ampl;
//	ampl = Abs(maxVal - minVal)*0x8000/diapason;
//	setAmplitude(ampl);
//
//	uint16_t setY;
//	setY = maxVal*0x8000/diapason - ampl;
//	setOffsetY(setY);
//}
//
////------------------------------------------------------------------------------------------------
//// инициализирует массив значений сигнала sin(x)
//void Sinus::setVal(void) { 
//
//	double offsetXrad = offsetX*PI/180;	// переводим градусы в радианы
//
//	double rad;
//	uint16_t value;
//
//	rad = 2*PI / diskret;
//
//	for (int i=0; i<diskret; i++)
//	{
//
//		// нужно подумать над проверкой
//		value = amplitude*sin(i * rad + offsetXrad) + offsetY;
//		if (value>0xFFFF) value=0xFFFF;
//		if (value<0x0) value=0x0;
//
//		val[i] = value&0xFFFF;
//
//	}
//}
