#ifndef LCDTWI_H_
#define LCDTWI_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "twi.h"
#define ADDRLSD 0b01111110		// адрес дисплея I2C // 7 бит адрес восьмой чтение или запись тут 0111111 это адрес и 0 чтение
																	//	1234567				8
//----------------------------------------
void LCD_ini(void);
void setpos(unsigned char x, unsigned y);
void str_lcd (char str1[]);

void clearlcd(void);
void sendcharlcd(unsigned char c);
//----------------------------------------
#define e1   I2C_SendByteByADDR(portlcd|=0x04,ADDRLSD) // установка линии E в 1
#define e0   I2C_SendByteByADDR(portlcd&=~0x04,ADDRLSD)  // установка линии E в 0
#define rs1    I2C_SendByteByADDR(portlcd|=0x01,ADDRLSD) // установка линии RS в 1
#define rs0   I2C_SendByteByADDR(portlcd&=~0x01,ADDRLSD)  // установка линии RS в 0
#define setled()    I2C_SendByteByADDR(portlcd|=0x08,ADDRLSD) // включение подсветки
#define setwrite()   I2C_SendByteByADDR(portlcd&=~0x02,ADDRLSD)  // установка записи в память дисплея
//----------------------------------------


#endif /* LCDTWI_H_ */