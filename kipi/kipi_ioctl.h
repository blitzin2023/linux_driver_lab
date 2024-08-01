#ifndef KIPI_IOCTL_H
#define KIPI_IOCTL_H

#include <linux/ioctl.h>

typedef struct {
	int cpu_nr;
	int ipi_nr;
} k_ioctl_ipi;

#define K_IOCTL_MAGIC		0x80

#define K_IOCTL_SEND_IPI	_IOW(K_IOCTL_MAGIC, 0, k_ioctl_ipi)


#endif
