#include <stdio.h>
#include "UartDrive.h"

static char dev[] = "/dev/ttyUSB0";

int main()
{
	int fd = 0xff;
	if (UART_SUCCESS != InitUartPort(dev, &fd))
	{
		printf("error\n");
		return 1;
	}

	UartReceiveData(fd);
	return 0;
}
