#include <linux/init.h>  
#include <linux/kernel.h>  
#include <linux/module.h>  
/* This function is called when the module is loade
d. */  
int simple_init(void)  
{  
       printk(KERN_INFO "Loading Module\n");  
       return 0;
}  
int simple_exit(void)  
{  
       printk(KERN_INFO "Removing Module\n");  
}  
/* Macros for registering module entry and exit poi
nts. */  
module_init(simple_init);  
module_exit(simple_exit);  
MODULE_LICENSE("GPL");  
MODULE_DESCRIPTION("Simple Module");  
MODULE_AUTHOR("SGG");  