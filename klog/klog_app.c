#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define KLOG_DEV "/dev/klog_dev" 

int main(int argc, char *argv[])
{
	int fd = open(KLOG_DEV, O_RDWR);
	if(fd < 0) {
		printf("blitz:%s:%d open %s failed\n", __FUNCTION__, __LINE__, KLOG_DEV);
		return -1;
	}

	write(fd, argv[1], strlen(argv[1]));

	close(fd);

	return 0;
}
