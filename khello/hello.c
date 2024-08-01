#include <linux/module.h>
#include <linux/kernel.h>

static int __init myinit(void)
{
	printk("blit:%s:%d\n", __FUNCTION__, __LINE__);
	return 0;
}

static void __exit myexit(void)
{
	printk("blit:%s:%d\n", __FUNCTION__, __LINE__);
}

module_init(myinit);
module_exit(myexit);

MODULE_LICENSE("GPL");

