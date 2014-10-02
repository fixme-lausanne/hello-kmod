/* vim: set ts=8 sw=8 tw=78 ai noexpandtab */

#include <linux/module.h>    // included for all kernel modules
#include <linux/kernel.h>    // included for KERN_INFO
#include <linux/init.h>      // included for __init and __exit macros

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lakshmanan");
MODULE_DESCRIPTION("A Simple Hello World module");

static struct timer_list my_timer;

void my_timer_callback( unsigned long data )
{
	int ret;

	printk( "my_timer_callback called (%ld).\n", jiffies );

	printk( "Starting timer to fire in 200ms (%ld)\n", jiffies );
	ret = mod_timer( &my_timer, jiffies + msecs_to_jiffies(200) );
	if (ret) printk("Error in mod_timer\n");
}

static int __init hello_init(void)
{
 	int ret;

	printk(KERN_INFO "Hello world!\n");

	setup_timer( &my_timer, my_timer_callback, 0 );
	ret = mod_timer( &my_timer, jiffies + msecs_to_jiffies(200) );
	if (ret) printk("Error in mod_timer\n");

	return 0;	// Non-zero return means that the module couldn't be loaded.
}

static void __exit hello_cleanup(void)
{
	int ret;

	ret = del_timer( &my_timer );
	if (ret) printk("The timer is still in use...\n");

	printk(KERN_INFO "Cleaning up module.\n");
}

module_init(hello_init);
module_exit(hello_cleanup);
