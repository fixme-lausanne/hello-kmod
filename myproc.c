#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>

#define MODNAME "FIXMYPROC"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rorist");
MODULE_DESCRIPTION("Create a file to read from");

static int hello_read_proc(char *buffer, char **start, off_t offset, int size, int *eof, void *data) {
    char *hello_str = "Hello, world!\n";
    int len = strlen(hello_str);
    if (size < len) return -EINVAL;
    if (offset != 0) return 0;
    strcpy(buffer, hello_str);
    *eof = 1;
    return len;
}

static int __init hello_init(void) {
    create_proc_read_entry("fixmyproc", 0, NULL, hello_read_proc, 54);
    printk(KERN_INFO "%s: Im loading!\n", MODNAME);
    return 0;
}

static void __exit hello_cleanup(void) {
    remove_proc_entry("fixmyproc", NULL);
    printk(KERN_INFO "%s: Im cleaning.\n", MODNAME);
}

module_init(hello_init);
module_exit(hello_cleanup);
