#define pr_fmt(fmt) KBUILD_MODNAME ":%s:%d: " fmt, __func__, __LINE__

#include <linux/module.h>
#include <linux/kernel.h>
//#include <linux/kobject.h>
#include <linux/device.h>  //DEVICE_ATTR()

static struct kobject *k_obj = NULL;

static ssize_t sysfs_demo_set_camvcc(struct device *d, struct device_attribute *attr,
             const char *buf, size_t count)
{
    int val;
    int err;

    err = kstrtoint(buf, 10, &val);
    if (err) {
        return err;
	}

	printk("get val %d\n", val);

    return count;
}

static ssize_t sysfs_demo_set_register(struct device *d, struct device_attribute *attr,
             const char *buf, size_t count)
{
    u8 page=0;
    u8 reg=0;
    u8 value=0;

    if (count == 0)
        return 0;

    if (sscanf(buf, "%hhx %hhx %hhx", &page, &reg, &value) != 3) {
        pr_info("not in hex or decimal form %s. read-->\n", buf);
        if (sscanf(buf, "%hhx %hhx", &page, &reg) != 2) {
            pr_info("not in hex or decimal form.%s\n", buf);
            return count;
        }
		pr_info("echo 0x%hhx 0x%hhx 0x%hhx > $reg\n", page, reg, value);

        return count;
    }

	pr_info("sysfs_demo_set_register 0x%hhx 0x%hhx = 0x%hhx\n", page, reg, value);

    return count;
}

static DEVICE_ATTR(camvcc, S_IWUSR | S_IRUGO, NULL, sysfs_demo_set_camvcc);
static DEVICE_ATTR(reg, S_IWUSR | S_IRUGO, NULL, sysfs_demo_set_register);

static struct attribute *sysfs_demo_attributes[] = {
	&dev_attr_camvcc.attr,
    &dev_attr_reg.attr,
    NULL
};

static const struct attribute_group sysfs_demo_group = {
    .attrs = sysfs_demo_attributes,
};

static int __init myinit(void)
{
	int ret;
	printk("blitz:%s:%d\n", __FUNCTION__, __LINE__);
	pr_info("blitz\n");

	if ((k_obj = kobject_create_and_add("sysfs_demo", NULL)) == NULL) {
		pr_err("sysfs_demo sys node create error \n");
		goto out;
	}

	/* Register sysfs hooks */
	/* echo "0x18 0x29 0x1" > /sys/sysfs_demo/reg */
    ret = sysfs_create_group(k_obj, &sysfs_demo_group);
    if (ret) {
        printk("sysfs_demo sysfs_create_group err %d \n",ret);
		goto out2;
    }

	return 0;
out2:
	kobject_put(k_obj);
out:
	return -1;
}

static void __exit myexit(void)
{
	printk("blitz:%s:%d\n", __FUNCTION__, __LINE__);
	if (k_obj) {
		sysfs_remove_group(k_obj, &sysfs_demo_group);
		kobject_put(k_obj);
	}
}

module_init(myinit);
module_exit(myexit);

MODULE_LICENSE("GPL");

