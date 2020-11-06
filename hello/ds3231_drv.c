#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>

static char hello_world[]="Hello World\n";

static dev_t hello_dev_number;
static struct cdev *driver_object;
static struct class *hello_class;
static struct device *hello_dev;

static int driver_open( struct inode *geraete_datei, struct file *instanz )
{
	dev_info( hello_dev, "driver_open called\n" );
	return 0;
}

static int driver_close( struct inode *geraete_datei, struct file *instanz )
{
	dev_info( hello_dev, "driver_close called\n" );
	return 0;
}

static ssize_t driver_read( struct file *instanz, char __user *user,
		size_t count, loff_t *offset )
{
	unsigned long not_copied, to_copy;

	to_copy = min( count, strlen(hello_world)+1 );
	not_copied=copy_to_user(user,hello_world,to_copy);
	*offset += to_copy-not_copied;
	return to_copy-not_copied;
}

static struct file_operations fops = {
	.owner= THIS_MODULE,
	.read= driver_read,
	.open= driver_open, 
	.release= driver_close,
};

static int __init mod_init( void )
{
	if (alloc_chrdev_region(&hello_dev_number,0,1,"ds3231_drv")<0)
		return -EIO;
	driver_object = cdev_alloc(); /* Anmeldeobjekt reservieren */
	if (driver_object==NULL)
		goto free_device_number;
	driver_object->owner = THIS_MODULE;
	driver_object->ops = &fops;
	if (cdev_add(driver_object,hello_dev_number,1))
		goto free_cdev;
	/* Eintrag im Sysfs, damit Udev den Geraetedateieintrag erzeugt. */
	hello_class = class_create( THIS_MODULE, "ds3231_drv" );
	if (IS_ERR( hello_class )) {
		pr_err( "hello: no udev support\n");
		goto free_cdev;
	}
	hello_dev = device_create( hello_class, NULL, hello_dev_number,
			NULL, "%s", "ds3231_drv" );
	if (IS_ERR( hello_dev )) {
		pr_err( "hello: device_create failed\n");
		goto free_class;
	}
	return 0;
free_class:
	class_destroy( hello_class );
free_cdev:
	kobject_put( &driver_object->kobj );
free_device_number:
	unregister_chrdev_region( hello_dev_number, 1 );
	return -EIO;
}

static void __exit mod_exit( void )
{
	/* Loeschen des Sysfs-Eintrags und damit der Geraetedatei */
	device_destroy( hello_class, hello_dev_number );
	class_destroy( hello_class );
	/* Abmelden des Treibers */
	cdev_del( driver_object );
	unregister_chrdev_region( hello_dev_number, 1 );
	return;
}

module_init( mod_init );
module_exit( mod_exit );

/* Metainformation */
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A virtual device, which returns hello.");
