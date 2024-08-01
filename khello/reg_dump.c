#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sizes.h>	//SZ_4K
#include <linux/io.h>		//ioremap

#define PMU_BASE 0x40500000

static int __init myinit(void)
{
	void __iomem *base;
	phys_addr_t start = PMU_BASE;
	u32 value; 

	base = ioremap(start, SZ_4K);
	if (!base)
	{
		printk("blit:%s:%d ioremap failed\n", __FUNCTION__, __LINE__);
		return false;
	}

	printk("blit:%s:%d \n", __FUNCTION__, __LINE__);
	value = readl(base);
	printk("blit:%s:%d value 0x%x\n", __FUNCTION__, __LINE__, value);

	iounmap(base);
	return 0;
}

static void __exit myexit(void)
{
	printk("blit:%s:%d\n", __FUNCTION__, __LINE__);
}

module_init(myinit);
module_exit(myexit);

MODULE_LICENSE("GPL");

