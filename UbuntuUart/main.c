#include <stdio.h>
#include "UartDrive.h"

static char dev[] = "/dev/ttyUSB0";

int main()
{
	int fd = 0xff;

	fd =  GetUartPortHandle(dev);
	if(fd != -1)
	{
		printf("open error\n");
	}
	while(1);
	
	if (UART_SUCCESS != InitUartPort(dev, &fd))
	{
		printf("error\n");
		return 1;
	}

	UartReceiveData(fd);
	while(1);
	return 0;
}

