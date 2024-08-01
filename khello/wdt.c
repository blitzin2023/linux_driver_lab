#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <asm/io.h>

//#define GPIO_BASE 0x30422000
#define GPIO_BASE 0x30420110
#define dir_reg  0x0 
#define out_reg  0x400

void gpio_wdt_ping(void)
{
	void __iomem *base=ioremap(GPIO_BASE, SZ_4K);
	u32 val;
	printk(KERN_EMERG "0x%p\n", base);
	if(!base)
		return;

	printk(KERN_EMERG "0x%p\n", base);

	while(1)
	{
		val = readl(base);
		printk(KERN_EMERG "val0 0x%x\n", val);
		val = val | 0x5;
		writel(val, base);
		printk(KERN_EMERG "write end");

		udelay(1);
		val = readl(base);
		printk(KERN_EMERG "val1 0x%x\n", val);
		val = val & ~(0x4);
		writel(val, base);
		msleep(500);
	}

	iounmap(base);
	return;

	val = readl(base+dir_reg);
	val = val | 1<<17;
	writel(base+dir_reg, val);

	val = readl(base+out_reg);
	val = val | 1<<17;
	writel(base+out_reg, val);


	printk(KERN_EMERG "-wdt feed dog\n");
	udelay(2000);

	val = readl(base+out_reg);
	val = val & ~(1<<17);
	writel(base+out_reg, val);
	udelay(2000);
	iounmap(base);
}

static int __init myinit(void)
{
	printk("blit:%s:%d\n", __FUNCTION__, __LINE__);
	gpio_wdt_ping();
	return 0;
}

static void __exit myexit(void)
{
	printk("blit:%s:%d\n", __FUNCTION__, __LINE__);
}

module_init(myinit);
module_exit(myexit);

MODULE_LICENSE("GPL");

