#include "RTC.h"
#define CODE1(X) (X/10+0x30)
#define CODE2(X) (X%10+0x30)
unsigned char RTC_ConvertFromDec(unsigned char c)
{
	unsigned char ch = ((c>>4)*10+(0b00001111&c));
	return ch;
}

unsigned char RTC_ConvertFromBinDec(unsigned char c)
{
	unsigned char ch = ((c/10)<<4)|(c%10);
	return ch;
}

void charToASCII_SUART(unsigned char c)
{
	unsigned char ch = (c/10+0x30);
	SOFT_UART_byte(ch);
	ch = c%10+0x30;
	SOFT_UART_byte(ch);
}

void charToASCII_LCD(unsigned char c)
{
	unsigned char ch = (c/10+0x30);
	sendcharlcd(ch);
	ch = c%10+0x30;
	sendcharlcd(ch);
}

void SetTime(void)
{
	I2C_StartCondition();
	//I2C_SendByteByADDR(0,0b11010000);	//переходим на адрес 0
	I2C_SendByte(0b11010000);
	I2C_SendByte(0);//Переходим на 0x00
	I2C_SendByte(RTC_ConvertFromBinDec(0)); //секунды
 	I2C_SendByte(RTC_ConvertFromBinDec(44)); //минуты
 	I2C_SendByte(RTC_ConvertFromBinDec(13)); //часы
 	I2C_SendByte(RTC_ConvertFromBinDec(4)); //день недели
 	I2C_SendByte(RTC_ConvertFromBinDec(23)); //дата
 	I2C_SendByte(RTC_ConvertFromBinDec(11)); //месяц
 	I2C_SendByte(RTC_ConvertFromBinDec(17)); //год
 	I2C_StopCondition();
	//SOFT_UART_send("SetTime(); OK!\n\r");
	
}

void GetTime(void)
{
	I2C_SendByteByADDR(0,0b11010000);	//переходим на адрес 0
	_delay_ms(10);
	I2C_StartCondition(); //Отправим условие START
	I2C_SendByte(0b11010001); //отправим в устройство бит чтения
	sec = I2C_ReadByte();
	min = I2C_ReadByte();
	hour = I2C_ReadByte();
	day = I2C_ReadByte();
	date = I2C_ReadByte();
	month = I2C_ReadByte();
	year = I2C_ReadLastByte();
	I2C_StopCondition(); //Отправим условие STOP
	//SOFT_UART_send("GetTime(); OK!\n\r");
	sec = RTC_ConvertFromDec(sec); //Преобразуем в десятичный формат
	min = RTC_ConvertFromDec(min); //Преобразуем в десятичный формат
	hour = RTC_ConvertFromDec(hour); //Преобразуем в десятичный формат
	day = RTC_ConvertFromDec(day); //Преобразуем в десятичный формат
	year = RTC_ConvertFromDec(year); //Преобразуем в десятичный формат
	month = RTC_ConvertFromDec(month); //Преобразуем в десятичный формат
	date = RTC_ConvertFromDec(date); //Преобразуем в десятичный формат
	
	
	/*
	SOFT_UART_byte(CODE1(date));//Преобразуем число в код числа
	SOFT_UART_byte(CODE2(date));//Преобразуем число в код числа
	SOFT_UART_byte('.');
	SOFT_UART_byte(CODE1(month));//Преобразуем число в код числа
	SOFT_UART_byte(CODE2(month));//Преобразуем число в код числа
	SOFT_UART_byte('.');
	SOFT_UART_byte(CODE1(year));//Преобразуем число в код числа
	SOFT_UART_byte(CODE2(year));//Преобразуем число в код числа
	SOFT_UART_byte('\t');
	SOFT_UART_byte(CODE1(hour));//Преобразуем число в код числа
	SOFT_UART_byte(CODE2(hour));//Преобразуем число в код числа
	SOFT_UART_byte(':');
	SOFT_UART_byte(CODE1(min));//Преобразуем число в код числа
	SOFT_UART_byte(CODE2(min));//Преобразуем число в код числа
	SOFT_UART_byte(':');
	SOFT_UART_byte(CODE1(sec));//Преобразуем число в код числа
	SOFT_UART_byte(CODE2(sec));//Преобразуем число в код числа
	SOFT_UART_byte('\t');*/
	/*
	sendcharlcd(CODE1(hour));
	sendcharlcd(CODE2(hour));
	sendcharlcd(':');
	sendcharlcd(CODE1(min));//Преобразуем число в код числа
	sendcharlcd(CODE2(min));//Преобразуем число в код числа*/
	
	
	setpos(12,0);
	charToASCII_LCD(hour);
	sendcharlcd(':');
	charToASCII_LCD(min);
	sendcharlcd(':');
	charToASCII_LCD(sec);
}