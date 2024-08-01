#include <linux/module.h>
#include <linux/fs.h>

static int major;

int grub_open(struct inode *inode, struct file *flip)
{
	return 0;
}

static ssize_t grub_read(struct file *filp, char __user *ubuf,
                  size_t count, loff_t *offp)
{
	printk("kyland:%s:%d\n", __FUNCTION__, __LINE__);
	return 0;
}
 static ssize_t grub_write(struct file *filp, const char __user *ubuf,
                  size_t count, loff_t *offp)
{
	int ret;
	char buf[256] = {0};
	if (!count)
	{
		printk("kyland:%s:%d\n", __FUNCTION__, __LINE__);
		return 0;
	}
		
	ret = copy_from_user(buf, ubuf, count);
	if (ret) {
		printk("kyland:%s:%d\n", __FUNCTION__, __LINE__);
		return 0;
		ret = -EFAULT;
	}
	printk("kyland:%s:%d %s\n", __FUNCTION__, __LINE__, buf);
	return ret;
}

static const struct file_operations grub_fops = {
	.open = grub_open,
	.read = grub_read,
	.write = grub_write,
};

static int __init grub_init(void)
{
	major = register_chrdev(0, "grub", &grub_fops);
	printk("kyland:%s:%d major:%d\n", __FUNCTION__, __LINE__, major);
	return 0;
}

static void __exit grub_exit(void)
{
	unregister_chrdev(major, "grub");
}

module_init(grub_init);
module_exit(grub_exit);
MODULE_LICENSE("GPL");
