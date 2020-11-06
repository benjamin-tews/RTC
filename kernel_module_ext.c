#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>  /* for put_user */
#include <asm/errno.h>
//Major number assigned to device driver
static int Major;


 MODULE_AUTHOR("benjamin.tews@iee.fraunhofer.de");
 MODULE_DESCRIPTION("My 1st Module");
 MODULE_LICENSE("GPL");

 int ret;

 static int device_open(struct inode *, struct file *);
 static int device_release(struct inode *, struct file *);
 static ssize_t device_read(struct file *, char *, size_t, loff_t *);
 static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

//device name as it appears in /proc/devices
#define DRIVER_NAME "My_Driver"


//fops must be declared after functions or the prototypes 
struct file_operations fops = {
        .open    = device_open,         //open device file
        .release = device_release,      //close device file
        .read    = device_read,         //read fromd evice
        .write   = device_write,        //write to device
};

static int mydriver_init(void) {
  printk(KERN_ALERT "Loading module ...\n");
  //ret = alloc_chrdev_region(&dev_no , 0, 1,DRIVER_NAME);
  ret = register_chrdev(Major, DRIVER_NAME, &fops);
  //if fails ...
  if (ret < 0) {
    printk(KERN_INFO "Major number allocation is failed\n");
    return ret;
  } else {
    //Major = MAJOR(dev_no);
    Major = register_chrdev(0, DRIVER_NAME, &fops);
    printk(KERN_INFO "The major number is %d",Major);
  }
  return 0;
}

 static void mydriver_exit(void) {
 printk(KERN_ALERT "Remove module ...\n"); /* 3) */
 //unregister_chrdev_region(dev_no, 1);
  unregister_chrdev(Major, DRIVER_NAME);
 }


//link load and release functions
 module_init(mydriver_init);
 module_exit(mydriver_exit);
