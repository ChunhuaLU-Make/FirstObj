#ifndef __UBUNTU_UART_H_
#define __UBUNTU_UART_H_

#include <stdio.h>

typedef enum __UartStatus_e
{
	UART_SUCCESS = 0,
	UART_ERROR,
	UART_OPEN_INBALID
	
}UartStatus_e;

int GetUartPortHandle(char *UartName);

UartStatus_e InitUartPort(char *UartName, int *fd) ;


int UartReceiveData(int fd);




#endif
