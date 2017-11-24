/*
 * Global_Variables.h
 *
 * Created: 20.10.2017 9:18:12
 *  Author: N
 */ 


#ifndef GLOBAL_VARIABLES_H_
#define GLOBAL_VARIABLES_H_

#define SUMSLAVE 10
unsigned int count;
char mode;
unsigned int responseStatus;
volatile uint8_t MasAddr[64];
volatile unsigned int MasAddrWCursor;
volatile unsigned int MasAddrCCursor;
unsigned char cmd[5];
#define LEN 128
volatile uint8_t bufferU[LEN];
char* MG;
char* SUBST;
char* PPM;
char* TEMP;
char* HYDR;
char* Trash;
unsigned int trigger;



#endif /* GLOBAL_VARIABLES_H_ */