Uart: UartDrive.o main.o
	gcc UartDrive.o main.o -o Uart
	rm -f *.o

UartDrive.o: UartDrive.c UartDrive.h
	gcc -c UartDrive.c

main.o: main.c
	gcc -c main.c


.PHONY:
GdbTest:
	gcc -g UartDrive.c main.c -o GdbTest
clean:
	rm -f Uart
