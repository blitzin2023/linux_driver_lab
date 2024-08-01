#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[])
{
	int fd = open("/dev/grub", O_RDWR);
	if(fd < 0)
		printf("kyland:%s:%d mknod /dev/grub c major 0\n", __FUNCTION__, __LINE__);
	write(fd, argv[1], strlen(argv[1]));
	close(fd);
	return 0;
}
