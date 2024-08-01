#include <linux/module.h>

static int __init hello_init(void)
{
	void *start;
	printk("kyland:%s:%d init\n", __FUNCTION__, __LINE__);
	start = phys_to_virt((phys_addr_t)0x400000);
	printk("kyland:%s:%d 0x%llx\n", __FUNCTION__, __LINE__, (unsigned long long )start);

	start = virt_to_phys((void *)0xffffffc010000000);
	printk("kyland:%s:%d virt_to_phys 0x%x\n", __FUNCTION__, __LINE__, start);
	start = virt_to_phys((void *)0xffffffc011677de0);
	printk("kyland:%s:%d virt_to_phys 0x%x\n", __FUNCTION__, __LINE__, start);

	start = __pa((void *)0xffffffc011677de0);
	printk("kyland:%s:%d __pa 0x%x\n", __FUNCTION__, __LINE__, start);
	start = __va((phys_addr_t)0x400000);
	printk("kyland:%s:%d __va 0x%llx\n", __FUNCTION__, __LINE__, start);

	printk("kyland:%s:%d 0x%x\n", __FUNCTION__, __LINE__, PAGE_OFFSET);

	start = virt_to_phys((void *)0xffffffc000000000);
	printk("kyland:%s:%d 0xffffffc000000000 -> 0x%x\n", __FUNCTION__, __LINE__, start);

	return 0;
}

static void __exit hello_exit(void)
{
	printk("kyland:%s:%d exit\n", __FUNCTION__, __LINE__);
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
