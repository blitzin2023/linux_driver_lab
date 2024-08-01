#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/module.h>
#include <linux/fs.h> //struct file_operations
#include <linux/uaccess.h> //copy_from_user

#include "kipi_ioctl.h"

#define NAME "kipi"

static int major = -1;
static struct cdev mycdev;
static struct class *myclass = NULL;

extern void TTOS_CPU_IPI_TEST(unsigned int cpu, unsigned int num);

int kipi_open(struct inode *inode, struct file *flip)
{
	return 0;
}

static ssize_t kipi_read(struct file *filp, char __user *ubuf,
                  size_t count, loff_t *offp)
{
	printk("blitz:%s:%d\n", __FUNCTION__, __LINE__);
	return 0;
}
 static ssize_t kipi_write(struct file *filp, const char __user *ubuf,
                  size_t count, loff_t *offp)
{
	int ret;
	char buf[256] = {0};
	if (!count)
	{
		printk("blitz:%s:%d\n", __FUNCTION__, __LINE__);
		return -EFAULT;
	}
		
	ret = copy_from_user(buf, ubuf, count);
	if (ret) {
		printk("blitz:%s:%d\n", __FUNCTION__, __LINE__);
		return -EFAULT;
	}
	printk("--> %s\n", buf);
	return ret;
}

static long kipi_ioctl(struct file *file, unsigned int cmd,
				unsigned long arg)
{
	void __user *arg_user = (void __user *)arg;
	int ret = 0;

	k_ioctl_ipi arg_ipi; 

	switch(cmd)
	{
	case K_IOCTL_SEND_IPI:
		if(copy_from_user(&arg_ipi, arg_user, sizeof(arg_ipi))) {
			printk("blitz: copy_to_user faild\n");
			ret = -EFAULT;
		} else {
			printk("blitz: cpu %d, ipi %d\n", arg_ipi.cpu_nr, arg_ipi.ipi_nr);
			TTOS_CPU_IPI_TEST(arg_ipi.cpu_nr, arg_ipi.ipi_nr);
		}
		break;
	default:	
		ret = -EINVAL;	
	}

	return ret;
}

static const struct file_operations kipi_fops = {
	.open = kipi_open,
	.read = kipi_read,
	.write = kipi_write,
	.unlocked_ioctl = kipi_ioctl
};

static void cleanup(int device_created)
{
    if (device_created) {
        device_destroy(myclass, major);
        cdev_del(&mycdev);
    }
    if (myclass)
        class_destroy(myclass);
    if (major != -1)
        unregister_chrdev_region(major, 1);
}

static int __init kipi_init(void)
{
	int device_created = 0;

	printk("blitz:%s:%d\n", __FUNCTION__, __LINE__);

	/* cat /proc/devices */
	if (alloc_chrdev_region(&major, 0, 1, NAME "_proc") < 0)
		goto error;
	/* ls /sys/class */
	if ((myclass = class_create(THIS_MODULE, NAME "_sys")) == NULL)
		goto error;
	/* ls /dev/ */
	if (device_create(myclass, NULL, major, NULL, NAME "_dev") == NULL)
    	goto error;
	device_created = 1;

	cdev_init(&mycdev, &kipi_fops);
	if (cdev_add(&mycdev, major, 1) == -1)
		goto error;

	return 0;

error:
	cleanup(device_created);
	return -1;
}

static void __exit kipi_exit(void)
{
	printk("blitz:%s:%d\n", __FUNCTION__, __LINE__);
	cleanup(1);
}

module_init(kipi_init);
module_exit(kipi_exit);

MODULE_LICENSE("GPL");

