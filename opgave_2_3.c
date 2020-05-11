#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/stat.h>
#include <linux/timer.h>
#include <asm/uaccess.h>

MODULE_LICENSE("Dual BSD/GPL");

static int major;
static int minor;
static const int amount = 1;

static const char driver_name[] = "hello_driver";

static struct cdev* device;
struct class *cl;

static int myint;
static int myint2;

module_param(myint, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(myint, "First integer");
module_param(myint2, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(myint2, "Second integer");

static int hello_open(struct inode *inode, struct file *file)
{
	printk(KERN_ALERT "hello_open()\n");
	return 0;
}

static int hello_release(struct inode *inode, struct file *file)
{
	printk(KERN_ALERT "hello_release()\n");
	return 0;
}

static ssize_t hello_read(struct file *file, char __user * buf, size_t lbuf, loff_t * ppos)
{
	printk(KERN_ALERT "READ: %ld\n", lbuf);
	return 0;
}

static ssize_t hello_write(struct file *file, const char __user * buf, size_t lbuf, loff_t * ppos)
{
	printk(KERN_ALERT "WRITE: %ld\n", lbuf);
	return lbuf;
}

struct file_operations fops = {
        .read = hello_read,
        .write = hello_write,
        .open = hello_open,
        .release = hello_release
};

static int hello_init(void)
{
	dev_t device_number;
	int result;

	device = cdev_alloc();
	cdev_init(device, &fops);

	result = alloc_chrdev_region(&device_number,0,1, driver_name);
	if(result < 0){
		printk("\n Error: alloc_chredev_region\n");
		return -1;
	}
	major = MAJOR(device_number);
	minor = MINOR(device_number);	
	
	device_number = MKDEV(major, minor);

	cdev_add(device, device_number, amount);

	cl = class_create(THIS_MODULE, driver_name);
	device_create(cl, NULL, device_number, NULL, "opgave2_3_dev");

	printk("Result: %d, MAJOR: %d, MINOR: %d\n", result, major, minor);
	printk(KERN_INFO "First integer: %d\n", myint);
	printk(KERN_INFO "Second integer: %d\n", myint2);
	return result;
}

static void hello_exit(void)
{
	dev_t device_number;
	printk(KERN_ALERT "hello_exit()\n");
	device_number = MKDEV(major, minor);
	unregister_chrdev_region(device, amount);

	device_destroy(cl, device_number);
	class_destroy(cl);
	cdev_del(device);
}

module_init(hello_init);
module_exit(hello_exit);

