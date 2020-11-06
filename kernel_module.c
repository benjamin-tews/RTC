#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>

 MODULE_AUTHOR("benjamin.tews@iee.fraunhofer.de");
 MODULE_DESCRIPTION("My 1st Module");
 MODULE_LICENSE("GPL");

 int ret;

//device name as it appears in /proc/devices
#define DRIVER_NAME "My_Driver"


static int mydriver_init(void) {
  printk(KERN_ALERT "Loading module ...\n");
  return 0;
}

static void mydriver_exit(void) {
  printk(KERN_ALERT "Remove module ...\n"); /* 3) */
  return 0;
}


//link load and release functions
 module_init(mydriver_init);
 module_exit(mydriver_exit);
