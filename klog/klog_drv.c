#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/module.h>
#include <linux/fs.h> //struct file_operations

#define NAME "klog"
static int major = -1;
static struct cdev mycdev;
static struct class *myclass = NULL;

int klog_open(struct inode *inode, struct file *flip)
{
	return 0;
}

static ssize_t klog_read(struct file *filp, char __user *ubuf,
                  size_t count, loff_t *offp)
{
	printk("blitz:%s:%d\n", __FUNCTION__, __LINE__);
	return 0;
}
 static ssize_t klog_write(struct file *filp, const char __user *ubuf,
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

static const struct file_operations klog_fops = {
	.open = klog_open,
	.read = klog_read,
	.write = klog_write,
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

static int __init klog_init(void)
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

	cdev_init(&mycdev, &klog_fops);
	if (cdev_add(&mycdev, major, 1) == -1)
		goto error;

	return 0;

error:
	cleanup(device_created);
	return -1;
}

static void __exit klog_exit(void)
{
	printk("blitz:%s:%d\n", __FUNCTION__, __LINE__);
	cleanup(1);
}

module_init(klog_init);
module_exit(klog_exit);

MODULE_LICENSE("GPL");

