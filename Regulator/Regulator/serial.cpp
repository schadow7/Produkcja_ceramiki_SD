#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <stdio.h>
#include <sys/ioctl.h> /* Dla ioctl */

#define cbInQueue 1024
#define cbOutQueue 16
int fd;
// Wlasne funkcje
int open(int fd, char * port) {
	struct termios options;
   
	fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY);
	if (fd < 0) {
		printf("Blad podczas otwierania portu\n");
		return -1;
	}
	else {
		/* Getting the current settings for the port */
		tcgetattr(fd, & options);
       
		/* Setting baudrate (19200) */
		cfsetispeed(& options, B9600);
		cfsetospeed(& options, B9600);
       
		options.c_cflag &= ~CSIZE; /* Wylaczenie maski bitowej */
		options.c_cflag |= CS8; /* Osiem bitow danch */
		options.c_cflag &= ~CSTOPB; /* 1 bit stopu */
		options.c_cflag |= PARENB; /* Wlacz kontrole parzystosci */
		options.c_cflag &= ~PARODD; /* even parity */
       
		options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); /* raw input (bez przetwarzania) */
       
		options.c_iflag &= ~(ICRNL | INLCR | IGNCR | IUCLC); /* Wylaczenie mapowania */
		options.c_iflag &= ~(IXON | IXOFF | IXANY); /* Wylaczenie kontroli przeplywu */
       
		options.c_oflag &= ~OPOST; /* Bez przetwarzania danych wyjsciowych */
       
		/* Setting the new settings for the port immediately */
		tcsetattr(fd, TCSANOW, & options);
		printf("Port otwarty i skonfigurowany\n");
		return fd;
	}
}

unsigned long read(const void* Buffer, unsigned long NumberOfBytesToWrite)
{
	int iOutWrite;
	if (fd < 1) return 0;
	iOutWrite = write(fd, Buffer, NumberOfBytesToWrite);
	if (iOutWrite < 0) return 0;
	return iOutWrite;
}
int read(void * Buffer,
	unsigned long * lpNumberOfBytesRead,
	unsigned long NumberOfBytesToRead)
{
	unsigned long nNumberOfBytesToRead;
	int iInRead;
	if (NumberOfBytesToRead > cbInQueue)
		nNumberOfBytesToRead = cbInQueue;
	else
		nNumberOfBytesToRead = NumberOfBytesToRead;
	if (fd < 1) return 0;
	iInRead = read(fd, Buffer, nNumberOfBytesToRead);
	if (iInRead < 0)
		return 0;
	else
		*lpNumberOfBytesRead = iInRead;
	return 1;
}
