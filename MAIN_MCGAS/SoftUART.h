#ifndef SOFTUART_H_
#define SOFTUART_H_

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CheckBit(reg,bit) (reg&(1<<bit)) //n=PIND&(1<<RX_PIN);

#define TX_PIN 3
#define RX_PIN 2
#define BTREIT 9600 //битрейт Ч 9600, при желании можно помен¤ть
#define MLN 1000000L //миллион

void SOFT_UART_init();						// Инициализация Програмного UART
void SOFT_UART_bit( char b);				// Отправка Бита
void SOFT_UART_byte( char a);				// Отправка Байта
void SOFT_UART_send( char *str);			// Отправка Строки
unsigned char SOFT_UART_read(void);			// Прием Строки
char *OperationResponse(void);				// Вернуть принятую строку обратно



#endif /* SOFTUART_H_ */