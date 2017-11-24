#include "UART_STDIO.h"
#include "Global_Variables.h"

static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);

#define BRC ((F_CPU/16/BAUD) - 1)

 void USARTinit(void)
 {	 
	 /*DDRD |=(1<<1);
	 PORTD |=(1<<1);
	 DDRD &= ~(1<<0);*/
	UBRR0H = (unsigned char)(BRC>>8);
	UBRR0L = (unsigned char)(BRC);
	//UCSR0A = (1<<RXC0)|(1<<TXC0)|(1<<UDRE0);
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
	 //Set frame Format: 8bit data, 2 stop bits
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);

	/*UCSR0A = 0;
	UCSR0B = 1<<RXEN0|1<<TXEN0|0<<RXCIE0|0<<TXCIE0;
	UCSR0C = 1<<USBS0|1<<UCSZ00|1<<UCSZ01;
*/


	 //DDRB |= (1<<PB5); //  pinMode(13,OUTPUT);

	 //blink13(3); //ready indication
	 IDX=0;
	 done=0;
	 sei();

	 stdout = &mystdout;
}
 

int uart_putchar(char c, FILE *stream)
{
   if (c == '\n')
   uart_putchar('\r', stream);
   loop_until_bit_is_set(UCSR0A, UDRE0);
   UDR0 = c;
   return 0;
}

void clearStr(char* str)
{
        for(IT=0;IT<LEN;IT++)
                str[IT]=0;
}

ISR(USART_RX_vect)
{		
		//cli();//MasAddr[0] = 0xFd;
		//SOFT_UART_send("RXInt");
		//PORTD &= ~(1<<(PORTD2));	// Прием
        uint8_t bf= UDR0;
		if (bf != 0x00)
		{
			bufferU[IDX]=bf;
// 			SOFT_UART_byte(bufferU[0]);
// 			SOFT_UART_byte(bufferU[1]);
// 			SOFT_UART_byte(bufferU[2]);
// 			SOFT_UART_byte(bufferU[3]);
			IDX++;
		}
       
		if (bf == 0x23)
		{
			//SOFT_UART_send(bufferU);
			switch (bufferU[2])
			{
				case 0x10:
					responseStatus = 2;
					break;
				case 0x11:	MasAddr[MasAddrWCursor] = bufferU[1];
					MasAddrWCursor++;
					//SOFT_UART_send(MasAddr);
					break;
				case 0x12:
				
					break;
				default:	//SOFT_UART_send("comand not found*");
					break;
			}
			IDX=0;
			
		}
		if (IDX == LEN)
		{
			IDX=0;
		}
		
		//sei();
}

