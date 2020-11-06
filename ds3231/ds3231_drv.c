#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/i2c.h>
#include <asm/uaccess.h>

static dev_t ds3231_drv_dev_number;
static struct cdev *driver_object;
static struct class *ds3231_drv_class;
static struct device *ds3231_drv_dev;
static struct i2c_adapter *adapter;
static struct i2c_client *slave;

static struct i2c_device_id ds3231_drv_idtable[] = {
        { "ds3231_drv", 0 }, { }
};
MODULE_DEVICE_TABLE(i2c, ds3231_drv_idtable);

const struct i2c_board_info info = {
                I2C_BOARD_INFO("ds3231_drv", 0x68)
        };

//static struct i2c_board_info info_20 = {
//    I2C_BOARD_INFO("ds3231_drv", 0x68),
//};

static ssize_t driver_write( struct file *instanz,
    const char __user *user, size_t count, loff_t *offset )
{
    unsigned long not_copied, to_copy;
    char value=0, buf[2];

    to_copy = min( count, sizeof(value) );
    not_copied=copy_from_user(&value, user, to_copy);
    to_copy -= not_copied;

    if( to_copy > 0 ) {
        buf[0] = 0x02; // output port 0
        buf[1] = value;
        i2c_master_send( slave, buf, 2 );
    }
    return to_copy;
}
static ssize_t driver_read( struct file *instanz,
    char __user *user, size_t count, loff_t *offset )
{
    unsigned long not_copied, to_copy;
    char value, command;

    command = 0x01; // input port 1
    i2c_master_send( slave, &command, 1 );
    i2c_master_recv( slave, &value, 1 );

    to_copy = min( count, sizeof(value) );
    not_copied=copy_to_user( user, &value, to_copy);
    return to_copy - not_copied;
}

static int ds3231_drv_probe( struct i2c_client *client,
    const struct i2c_device_id *id )
{
    char buf[2];

    printk("ds3231_drv_probe: %p %p \"%s\"- ",client,id,id->name);
    printk("slaveaddr: %d, name: %s\n",client->addr,client->name);
    if (client->addr != 0x68 ) {
        printk("i2c_probe: not found\n");
        return -1;
    }
    slave = client;
    // configuration
    buf[0] = 0x06; // direction port 0
    buf[1] = 0x00; // output
    i2c_master_send( client, buf, 2 );
    return 0;
}

static int ds3231_drv_remove( struct i2c_client *client )
{
    return 0;
}
static struct file_operations fops = {
    .owner= THIS_MODULE,
    .write= driver_write,
    .read = driver_read,
};

static struct i2c_driver ds3231_drv_driver = {
        .driver = {
                .name   = "ds3231_drv",
        },
        .id_table       = ds3231_drv_idtable,
        .probe          = ds3231_drv_probe,
        .remove         = ds3231_drv_remove,
};

static int __init mod_init( void )
{
    if (alloc_chrdev_region(&ds3231_drv_dev_number,0,1,"ds3231_drv")<0 )
        return -EIO;
    driver_object = cdev_alloc();
    if (driver_object==NULL )
        goto free_device_number;
    driver_object->owner = THIS_MODULE;
    driver_object->ops = &fops;
    if (cdev_add(driver_object,ds3231_drv_dev_number,1) )
        goto free_cdev;
    ds3231_drv_class = class_create( THIS_MODULE, "ds3231_drv" );
    if (IS_ERR( ds3231_drv_class ) ) {
        pr_err( "ds3231_drv: no udev support\n");
        goto free_cdev;
    }
    ds3231_drv_dev = device_create( ds3231_drv_class, NULL,
	ds3231_drv_dev_number, NULL, "%s", "ds3231_drv" );
    dev_info(ds3231_drv_dev, "mod_init\n");

    if (i2c_add_driver(&ds3231_drv_driver)) {
        pr_err("i2c_add_driver failed\n");
        goto destroy_dev_class;
    }
    adapter = i2c_get_adapter(1); // Adapter sind durchnummeriert
    if (adapter==NULL) {
        pr_err("i2c_get_adapter failed\n");
        goto del_i2c_driver;
    }
    slave = i2c_new_device( adapter, &info );
    if (slave==NULL) {
        pr_err("i2c_new_device failed\n");
        goto del_i2c_driver;
    }
    return 0;
del_i2c_driver:
    i2c_del_driver(&ds3231_drv_driver);
destroy_dev_class:
    device_destroy( ds3231_drv_class, ds3231_drv_dev_number );
    class_destroy( ds3231_drv_class );
free_cdev:
    kobject_put( &driver_object->kobj );
free_device_number:
    unregister_chrdev_region( ds3231_drv_dev_number, 1 );
    return -EIO;
}

static void __exit mod_exit( void )
{
    dev_info(ds3231_drv_dev, "mod_exit");
    device_destroy( ds3231_drv_class, ds3231_drv_dev_number );
    class_destroy( ds3231_drv_class );
    cdev_del( driver_object );
    unregister_chrdev_region( ds3231_drv_dev_number, 1 );
    i2c_unregister_device( slave );
    i2c_del_driver(&ds3231_drv_driver);
    return;
}
module_init( mod_init );
module_exit( mod_exit );
MODULE_LICENSE("GPL");
