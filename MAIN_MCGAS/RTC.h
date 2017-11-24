#ifndef RTC_H_
#define RTC_H_
unsigned char sec,min,hour,day,date,month,year;
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "SoftUART.h"
#include "twi.h"
#include "lcdtwi.h"
void charToASCII_SUART(unsigned char c);
void charToASCII_LCD(unsigned char c);
void SetTime(void);
void GetTime(void);
#endif /* RTC_H_ */