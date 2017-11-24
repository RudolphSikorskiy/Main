/*
 * UART_STDIO.h
 *
 * Created: 07.07.2017 14:51:55
 *  Author: N
 */ 


#ifndef UART_STDIO_H_
#define UART_STDIO_H_


#define F_CPU 16000000UL
#define BAUD 9600
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Global_Variables.h"
#include "twi.h"
#include "lcdtwi.h"
#include "SoftUART.h"

register unsigned char IT asm("r16");
volatile unsigned char done;
volatile unsigned char IDX;

void USARTinit(void);
int uart_putchar(char c, FILE *stream);
void clearStr(char* str);
void blink13(uint8_t count);



#endif /* UART_STDIO_H_ */