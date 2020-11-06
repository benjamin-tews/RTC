#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>

#define TEMPLATE "mydriver" /* Name des Moduls */

static dev_t template_dev_number;
static struct cdev *driver_object;
struct class *template_class;

static struct file_operations fops = {
	/* Hier werden die Adressen der eigentlichen
	 * Treiberfunktionen abgelegt.
	 */
};

static int __init mydriver_init( void )
{
	if (alloc_chrdev_region(&template_dev_number,0,1,TEMPLATE)<0)
		return -EIO;
	driver_object = cdev_alloc(); /* Anmeldeobjekt reservieren */
	if (driver_object==NULL)
		goto free_device_number;
	driver_object->owner = THIS_MODULE;
	driver_object->ops = &fops;
	if (cdev_add(driver_object,template_dev_number,1))
		goto free_cdev;
	/* Eintrag im Sysfs, damit Udev den Geraetedateieintrag erzeugt. */
	template_class = class_create( THIS_MODULE, TEMPLATE );
	if (IS_ERR(template_class))
		goto free_cdev;
	device_create( template_class, NULL, template_dev_number,
			NULL, "%s", TEMPLATE );
	return 0;
free_cdev:
	kobject_put( &driver_object->kobj );
free_device_number:
	unregister_chrdev_region( template_dev_number, 1 );
	return -EIO;
}

static void __exit mydriver_exit( void )
{
	/* Loeschen des Sysfs-Eintrags und damit der Geraetedatei */
	device_destroy( template_class, template_dev_number );
	class_destroy( template_class );
	/* Abmelden des Treibers */
	cdev_del( driver_object );
	unregister_chrdev_region( template_dev_number, 1 );
	return;
}

module_init( mydriver_init );
module_exit( mydriver_exit );
MODULE_AUTHOR("benjamin.tews@iee.fraunhofer.de");
MODULE_DESCRIPTION("My 1st mydriver");
MODULE_LICENSE( "GPL" );
