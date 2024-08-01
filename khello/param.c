/*
 * Install module:
 * 	  insmod param.ko val=993 loc=23 
 *
 * Query value:	
 * 	  cat /sys/module/param/parameters/val
 *    cat /sys/module/param/parameters/loc
 *
 */
#define pr_fmt(fmt) KBUILD_MODNAME ":%s:%d: " fmt, __func__, __LINE__

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>

static unsigned long val = 0;
module_param(val, ulong, 0644);
MODULE_PARM_DESC(val, "A unsigned long variable");

static unsigned long loc = 0;
module_param(loc, ulong, 0644);
MODULE_PARM_DESC(loc, "A unsigned long variable");

static int cpu_test(void)
{
	int cpu;
	int i;
	const struct cpumask *mask;

	for(i=0; i<8; i++)
	{
		pr_info("%s %d: mask CPU %d\n", __FUNCTION__, __LINE__, i);
		mask = cpumask_of(i);
		for_each_cpu(cpu, mask)
			pr_info("%s %d: %d is masked\n", __FUNCTION__, __LINE__, cpu);
	}

	for_each_present_cpu(cpu)
		pr_info("%s %d: %d is present\n", __FUNCTION__, __LINE__, cpu);

	for_each_online_cpu(cpu)
		pr_info("%s %d: %d is online\n", __FUNCTION__, __LINE__, cpu);

	for_each_possible_cpu(cpu)
		pr_info("%s %d: %d is possible\n", __FUNCTION__, __LINE__, cpu);

	return 0;
}

static int __init myinit(void)
{
	unsigned long size = 32;
	unsigned long bit = find_next_zero_bit(&val, size, loc);
	pr_info("%s %d: %lu\n", __FUNCTION__, __LINE__, bit);
	pr_info("val:%ld loc:%ld\n", val, loc);

	cpu_test();
	return 0;
}

static void __exit myexit(void)
{
	pr_info("%s %d\n", __FUNCTION__, __LINE__);
}

module_init(myinit);
module_exit(myexit);

MODULE_LICENSE("GPL");

