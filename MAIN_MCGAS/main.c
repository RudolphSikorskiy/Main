/*
 * Main_v2.c
 *
 * Created: 19.10.2017 13:53:56
 * Author : N
 */ 


#include "main.h"

// 0 - ������������� 1 - ����� ��������� �������
void Initialization(void);
void DataPackageFormation(char data[]);
ISR(TIMER1_OVF_vect)
{
	//cli();
	
	count++;
	switch (mode)
	{
	case 0x35:
		if (count>4)
		{
			mode = 0x30;
			clearlcd();
			count = 0;
		}
		mode = 0x31;
		break;
	}

	
	
	GetTime();	// �������� ����� � ������ ������ � ������!
	//SetTime();	
	
	TCNT1=49911;//��������� �������� �������
	//sei();//��������� ����������
}


int main(void)
{
    DDRD = 0xFF;
	cmd[0] = 0x10;
	cmd[1] = 0x11;
	cmd[2] = 0x12;
	cmd[3] = 0x13;
	cmd[4] = 0x14;
	mode = 0x30;
	count = 0;
	responseStatus = 0;			// ������ �� ��������� ������ �� ��������� ������ �� 0�10 ������ ���� � 0
	IDX = 0;
	TEMP = "00";
	HYDR =  "00";
	
// 	TEMP[0] = '0';
// 	TEMP[1] = '0';
// 	HYDR[0] = '0';
// 	HYDR[1] = '0';
	//PORTD |= (1<<(PORTD4));				// ��������
	
	USARTinit(); //207 -> 9600 ��� 16Mhz 51-> 19200
	SOFT_UART_init();						// ������������� ����������� UART
	I2C_Init();
	LCD_ini();							//�������������� �������
	clearlcd();
	//setpos(7,1);
	//str_lcd("MC-GAS");
	SOFT_UART_send("\n\rMC-GAS\n\r");
	_delay_ms(2000);
	TCCR1B|=(1<<CS12)|(1<<CS10);//������������ = 1024
	TIMSK1|=(1<<TOIE1);//��������� ���������� �� ������������ ������� 1
	TCNT1=49911;//��������� �������� �������
	//SetTime();
	sei();//��������� ����������
	
    while (1) 
    {
		
		switch (mode)
		{
			case 0x30:
				//SOFT_UART_send("Init\n\r");
				Initialization();	// ��������� ������� ������� ������ � ��
				
				mode = 0x35;			// ��������� ������ ������ ���������� �������
				//TCNT1=49991;//��������� �������� �������
				break;
			case 0x31:
				
				//SOFT_UART_send("survey of followers: ");
// 				SOFT_UART_send(MasAddr);
// 				SOFT_UART_byte(' ');
// 				setpos(12,1);
// 				str_lcd("T   H   ");
// 				setpos(14,1);
// 				str_lcd(TEMP);
// 				setpos(18,1);
// 				str_lcd(HYDR);
				charToASCII_SUART(date);
				SOFT_UART_byte('.');
				charToASCII_SUART(month);
				SOFT_UART_byte('.');
				charToASCII_SUART(year);
				SOFT_UART_byte(' ');
				charToASCII_SUART(hour);
				SOFT_UART_byte(':');
				charToASCII_SUART(min);
				SOFT_UART_byte(':');
				charToASCII_SUART(sec);
				SOFT_UART_send(" \t ");
				//SOFT_UART_send("\n\r");
				for (int i = 0;i < MasAddrWCursor;i++)
				{
					MasAddrCCursor  = i;
					PORTD |= (1<<(PORTD4));				// ��������
					_delay_us(2000);					// 1 �� �������
					printf("%c%c%c%c",'@',MasAddr[i],cmd[0],'#');	// ����� ����������������� ������� ������� ������ ������
					_delay_us(2000);						// 1500 �� �������
					PORTD &= ~(1<<(PORTD4));			// �����
					_delay_ms(40);						// 10 - 100 �� ������� 
					if (responseStatus == 2)
					{
						//SOFT_UART_byte(mode);
						responseStatus = 1;
						if (responseStatus == 1)
						{
							DataPackageFormation(bufferU);
							responseStatus = 2;
							
						}
						if (strlen(TEMP)>2 || strlen(HYDR)>2 || TEMP[0]=='#' || HYDR[0]=='#')
						{
							SOFT_UART_send(SUBST);
							SOFT_UART_byte(' ');
							SOFT_UART_send("0.000");
							SOFT_UART_byte(' ');
							SOFT_UART_send("0000");
							SOFT_UART_byte(' ');
							SOFT_UART_send("00");
							SOFT_UART_byte(' ');
							SOFT_UART_send("00");
							SOFT_UART_byte(' ');
							SOFT_UART_send(" \t ");
						} 
						else
						{
							
							if (MasAddrCCursor>3)
							{
								setpos(10,MasAddrCCursor-2);
								str_lcd("          ");
								setpos(12,MasAddrCCursor-2);
								str_lcd(SUBST);
								setpos(15,MasAddrCCursor-2);
								str_lcd(MG);
							}else
							{
								setpos(0,MasAddrCCursor);
								str_lcd("            ");
								setpos(0,MasAddrCCursor);
								str_lcd(SUBST);
								setpos(4,MasAddrCCursor);
								str_lcd(MG);
							}
							
							
							SOFT_UART_send(SUBST);
							SOFT_UART_byte(' ');
							SOFT_UART_send(MG);
							SOFT_UART_byte(' ');
							SOFT_UART_send(PPM);
							SOFT_UART_byte(' ');
							SOFT_UART_send(TEMP);
							SOFT_UART_byte(' ');
							SOFT_UART_send(HYDR);
							SOFT_UART_byte(' ');
							SOFT_UART_send(" \t ");
							responseStatus = 0;
						}
						
						
					}
				}
				mode = 0x35;
				setpos(12,1);
				str_lcd("T   H   ");
				setpos(14,1);
				str_lcd(TEMP);
				setpos(18,1);
				str_lcd(HYDR);
				SOFT_UART_send("\n\r");
				//TCNT1=49991;//��������� �������� �������
				/*setpos(0,3);
		
				str_lcd("addr> ");
				str_lcd(MasAddr);*/
				
				//MasAddr[0] = '\0';	
				break;
			case 0x32:
				
				for (int i = 0;i<sizeof(bufferU);i++) // ������� ������
				{
					bufferU[i]=0;
				}
				break;
			case 0x35:
				//_delay_us(100);
				
				for (int i = 0;i<sizeof(bufferU);i++) // ������� ������
				{
					bufferU[i]=0;
				}
				break;
			
			default:
				break;	
	
		}
		
		
		
    }
}

void Initialization(void)
{
	MasAddrWCursor = 0;			// ������ ��� ������� ��������� ������������
	for (char i = 0xF9;i < 0xFF;i++)
	{
		_delay_ms(1);									// �������� ��� ������ ������ � ������
		PORTD |= (1<<(PORTD4));							// ��������
		_delay_us(2000);
		printf("%c%c%c%c",'@',i,cmd[1],'#');						// ������������ ��������� ������������ 0�31-0�FF �������� �������� ������
		//printf("1");
		_delay_us(2000);
		PORTD &= ~(1<<(PORTD4));						// �����
		_delay_ms(10);									// �������� ��� ������ ������ � ������
	}
	
	
}


void DataPackageFormation(char data[])
{
	//setpos(0,1);
	//str_lcd(data);
	char *pch = strtok (data,", "); //�� ������ ��������� ������� ����������� (������, �������, �����)
	while (pch != NULL) //���� ���� ������� pch !== NULL � ������ ��������� ������ 4
	{	//		0		1	2	3	4		5		6	7	 8	 9	 10
		//111116010250, 13, 25, 51, 13143, 27064, 30330, 00, 03, 43, 30
		//addr+cmd		H2S	Mg	ppm	Temp	Hydr
		switch ( trigger )
		{
			//----------------------------//

			case 1:
			SUBST = pch;
			pch = strtok (NULL, ", ");
			trigger++;
			break;

			//----------------------------//

			case 2:
			MG = pch;
			pch = strtok (NULL, ", ");
			trigger++;
			break;

			//----------------------------//

			case 3:
			PPM = pch;
			pch = strtok (NULL, ", ");
			trigger++;
			break;

			//----------------------------//

			case 4:
			TEMP = pch;
			pch = strtok (NULL, ", ");
			trigger++;
			break;

			//----------------------------//

			case 5:
			HYDR = pch;
			pch = strtok (NULL, ", ");
			trigger++;
			break;

			//----------------------------//


			default:
			Trash = pch;
			pch = strtok (NULL, ", ");
			trigger++;
			break;
		}

	}
	trigger = 0;


}