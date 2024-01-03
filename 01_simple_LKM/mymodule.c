#include <linux/module.h>
#include <linux/init.h>

/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Fab");
MODULE_DESCRIPTION("A hello world LKM");

/**
 * @brief This function is called, when the module is loaded into the kernel
 */
static int __init my_init(void) {
	printk("Hello, Kernel!\n");
	return 0;
}

/**
 * @brief This function is called, when the module is removed from the kernel
 */
static void __exit my_exit(void) {
	printk("Goodbye, Kernel\n");
}

module_init(my_init);
module_exit(my_exit);


/*
make KERNEL=/home/fabricio/Downloads/linux-5.4.65/  
CROSS=/home/fabricio/Downloads/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi- all
modinfo ./mymodule.ko
*/
