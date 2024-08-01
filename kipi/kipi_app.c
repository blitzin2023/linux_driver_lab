#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include "kipi_ioctl.h"

#define KIPI_DEV "/dev/kipi_dev" 

int main(int argc, char *argv[])
{
	k_ioctl_ipi k_ipi;
	char *endptr;
	int ret;
	int fd;

	if(argc != 3)
	{
		printf("Usage:%s <cpu> <ipi_num>\n", argv[0]);
		return -1;
	}

	k_ipi.cpu_nr = strtol(argv[1], &endptr, 10);
	if(*endptr != '\0')
	{
		printf("Invalid character: %c\n", *endptr);
		return -1;
	}

	k_ipi.ipi_nr = strtol(argv[2], &endptr, 10);
	if(*endptr != '\0')
	{
		printf("Invalid character: %c\n", *endptr);
		return -1;
	}

	fd = open(KIPI_DEV, O_RDWR);
	if(fd < 0) {
		printf("blitz:%s:%d open %s failed\n", __FUNCTION__, __LINE__, KIPI_DEV);
		return -1;
	}

	ret = ioctl(fd, K_IOCTL_SEND_IPI, &k_ipi);
	if(ret == 0)
	{
		printf("---> CPU %d, ipi %d\n", k_ipi.cpu_nr, k_ipi.ipi_nr);  
	} else {
		printf("Failed\n");  
	}

	close(fd);

	return 0;
}
