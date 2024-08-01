#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/io.h> //ioremap readl

#define ETHERNET2_BASE 0x38500000

static int __init myinit(void)
{
	void __iomem *reg = NULL;
	printk("blit:%s:%d\n", __FUNCTION__, __LINE__);

	reg = ioremap(ETHERNET2_BASE, 3064*1024);
	printk("\t\t %s\t value:0x%08X\n","INPUT_SELECT_ETHERNET2_MDIO",readl(reg+(0x454<<10)));
	printk("\t\t %s\t value:0x%08X\n","PIN_MUX_GPIO_D10",readl(reg+(0x268<<10)));

	return 0;
}

static void __exit myexit(void)
{
	printk("blit:%s:%d\n", __FUNCTION__, __LINE__);
}

module_init(myinit);
module_exit(myexit);

MODULE_LICENSE("GPL");

