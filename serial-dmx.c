#include "lpc17xx_uart.h"	
#include "lpc_types.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

#include "serial-dmx.h"	
#include "pindef.h"


// CONSTRUCTOR
DMX::DMX()
{	
	pinconf(SERIALTX);
	pinconf(SERIALRX);

	init();
}

// PROTECTED
void DMX::init()
{
	UART_CFG_Type cfg;	
	UART_FIFO_CFG_Type UARTFIFOConfigStruct;
	
	UART_ConfigStructInit(&cfg);
	UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);

	cfg.Baud_rate = 250000;
	cfg.Stopbits = UART_STOPBIT_2;

	UART_Init((LPC_UART_TypeDef *)LPC_UART1, &cfg);		 
	UART_FIFOConfig((LPC_UART_TypeDef *)LPC_UART1, &UARTFIFOConfigStruct);	
	UART_TxCmd((LPC_UART_TypeDef *)LPC_UART1, ENABLE);		
}

// PUBLIC
int DMX::write(char * buf, int length)
{
	return(UART_Send((LPC_UART_TypeDef *)LPC_UART1,(uint8_t *)buf,length, BLOCKING));
}

void DMX::send_break()
{
	LPC_UART1->LCR |= UART_LCR_BREAK_EN;
}

void DMX::end_break()
{
	LPC_UART1->LCR &= !UART_LCR_BREAK_EN;
}
