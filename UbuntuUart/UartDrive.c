#include "UartDrive.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <strings.h>
#include <stdint.h>



/**
 *Open the uart port fd.
 * @UartName The uart port.
 */
int GetUartPortHandle(char *UartName)
{
	int UartFd = 0xFF;
	
	if(UartName == NULL)
	{
		return -1;
	}

	/* Open the uart port. return fd.*/
	UartFd = open(UartName,O_RDWR | O_NOCTTY | O_NONBLOCK);
	if(UartFd==-1)
	{
		perror("Can't Open SerialPort");
	}

	if(fcntl(UartFd, F_SETFL, 0) < 0)  
    {  
        perror("fcntl F_SETFL\n");  
        return -1;  
    }  

	 if(isatty(STDIN_FILENO) == 0)  
     {  
        perror("standard input is not a terminal device");  
        return -1;  
     }  
	 
	return UartFd;
}

UartStatus_e InitUartPort(char *UartName, int *fd) 
{
	int UartFd = 0xFF;
	
	struct termios newtio,oldtio;

	UartFd = GetUartPortHandle(UartName);
	if(UartFd == -1)
	{
		return UART_OPEN_INBALID;
	}
		
	if ( tcgetattr( UartFd, &oldtio)  != 0)
	{  
      	perror("SetupSerial 1");
		printf("tcgetattr( fd,&oldtio) -> %d\n",tcgetattr( UartFd,&oldtio)); 
      	return UART_ERROR; 
     }

		/* Newtio set zero. */
	 bzero( &newtio, sizeof( newtio ) );

		/* Set the char size. */
	 newtio.c_cflag |= CLOCAL | CREAD;  
     newtio.c_cflag &= ~CSIZE; 

	/* Set the stop bit.*/
	 newtio.c_cflag |= CS8; 

	 /*Set parity check bit, not*/
	 newtio.c_cflag &= ~PARENB; 

		/* Set Baud rate to 9600. */
	 cfsetispeed(&newtio, B9600); 
     cfsetospeed(&newtio, B9600);

	 /* Set one stop bit.*/
	 newtio.c_cflag &= ~CSTOPB;

	 /* Set special control char.*/
	 newtio.c_cc[VTIME]  = 150; 
     newtio.c_cc[VMIN] = 0;

	/* Clean inout/ouput data. */
	 tcflush(UartFd, TCIFLUSH); 

	 
	if((tcsetattr(UartFd,TCSANOW,&newtio))!=0) 
	 { 
	  	perror("com set error"); 
	  	return UART_ERROR; 
	 }

	*fd = UartFd;
	printf("set done!\n"); 
	return UART_SUCCESS; 
}

int UartReceiveData(int fd)
{
	uint8_t buff;
	ssize_t size = 0; 
	while(1)
	{
		size = read(fd, &buff, 1);	//Receive data.
		if(size != 0)
		{
			printf("%c", (char)buff);
		}
		usleep(10000);	//Delay 10ms
	}
}


