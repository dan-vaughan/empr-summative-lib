#include "lpc17xx_uart.h"	
#include "lpc_types.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "lpc17xx_gpio.h"

#include "serial.h"	
#include "pindef.h"


// CONSTRUCTOR
Serial::Serial(int mod)
{	
	module = mod;
	if (module == 1) {
		pinconf(USBTX);
		pinconf(USBRX);
	}
	else if (module == 2) {
		pinconf(SERIALTX);
		pinconf(SERIALRX);
	}

	init();
}

// PROTECTED
void Serial::init()
{
	UART_CFG_Type UARTConfigStruct;	
	UART_FIFO_CFG_Type UARTFIFOConfigStruct;
	
	UART_ConfigStructInit(&UARTConfigStruct);
	UART_FIFOConfigStructInit(&UARTFIFOConfigStruct);	

	if (module == 1) {
		
		UART_Init((LPC_UART_TypeDef *)LPC_UART0, &UARTConfigStruct);		 
		UART_FIFOConfig((LPC_UART_TypeDef *)LPC_UART0, &UARTFIFOConfigStruct);	
		UART_TxCmd((LPC_UART_TypeDef *)LPC_UART0, ENABLE);		
	}
	else if (module == 2) {
		UARTConfigStruct.Stopbits = UART_STOPBIT_2;
		UARTConfigStruct.Baud_rate = 250000;
		UART_Init((LPC_UART_TypeDef *)LPC_UART1, &UARTConfigStruct);		 
		UART_FIFOConfig((LPC_UART_TypeDef *)LPC_UART1, &UARTFIFOConfigStruct);	
		UART_TxCmd((LPC_UART_TypeDef *)LPC_UART1, ENABLE);		
	}
}

// PUBLIC
void Serial::printf(char * buf, ...)
{
	va_list arg;
	va_start(arg, buf);
	
	char temp[500];
	vsprintf(temp, buf, arg);

	int len = strlen(temp)+1;

	write(temp, len);

	va_end(arg);	
}

int Serial::write(char * buf, int length)
{
	if (module == 1) {
		return(UART_Send((LPC_UART_TypeDef *)LPC_UART0,(uint8_t *)buf,length, BLOCKING));
	}
	else if (module == 2) {
		return(UART_Send((LPC_UART_TypeDef *)LPC_UART1,(uint8_t *)buf,length, BLOCKING));
	}
}

void Serial::sendbreak()
{
	if (module == 1) {
		UART_ForceBreak((LPC_UART_TypeDef *)LPC_UART0);
	}
	if (module == 2) {
		UART_ForceBreak((LPC_UART_TypeDef *)LPC_UART1);
	}
}

