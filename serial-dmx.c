#include "lpc17xx_uart.h"	
#include "lpc_types.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

#include "serial-dmx.h"	
#include "pindef.h"
#include "utilities.h"


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
	cfg.Databits = UART_DATABIT_8;	

	UART_Init((LPC_UART_TypeDef *)LPC_UART1, &cfg);		 
	//LPC_UART1->IER |= (1 << 2); //Enable interrupt register
	UART_FIFOConfig((LPC_UART_TypeDef *)LPC_UART1, &UARTFIFOConfigStruct);	
	UART_TxCmd((LPC_UART_TypeDef *)LPC_UART1, ENABLE);		

	//Enable Receive Interrupt (RBR) and Line Status Interrupt (RLS)

//	int temp = UART_INTCFG_RBR | UART_INTCFG_RLS;

//	UART_IntConfig((LPC_UART_TypeDef *)LPC_UART1, (UART_INT_Type)temp, ENABLE);
//	UART_IntConfig((LPC_UART_TypeDef *)LPC_UART1, UART_INTCFG_RBR, ENABLE);
	UART_IntConfig((LPC_UART_TypeDef *)LPC_UART1, UART_INTCFG_RLS, ENABLE);

//	NVIC_SetPriorityGrouping(0);
//	uint32_t tmp = NVIC_GetPriority(UART1_IRQn);
	
//	NVIC_SetPriority(UART1_IRQn, ((0x01<<3)|0x01));
//	NVIC_SetPriority(UART1_IRQn, (0x01<<4));

	
//	NVIC_EnableIRQ(UART1_IRQn);

}

// PUBLIC
void DMX::send(char * buf, int length)
{
	write(buf, length);
	delay(1000);
	send_break();
	delay(1000);
	end_break();
	delay(40);

}


int DMX::write(char * buf, int length)
{
	return(UART_Send((LPC_UART_TypeDef *)LPC_UART1,(uint8_t *)buf,length, BLOCKING));
}

int DMX::read(uint8_t* buf)
{	
	int length = sizeof(buf)/sizeof(uint8_t);
	return(UART_Receive((LPC_UART_TypeDef *)LPC_UART1,buf,length, NONE_BLOCKING));
}

void DMX::send_break()
{
	LPC_UART1->LCR |= UART_LCR_BREAK_EN;	//Set bit 6 to 1
}

void DMX::end_break()
{
	LPC_UART1->LCR &= ~UART_LCR_BREAK_EN;	//Set bit 6 to 0
}



