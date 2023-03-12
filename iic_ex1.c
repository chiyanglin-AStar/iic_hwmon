#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include <linux/i2c.h>
#include <linux/input.h>
//include <linux/earlysuspend.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/irq.h>
//#include <linux/ioc4.h>
#include <linux/io.h>

#include <linux/proc_fs.h>
/*
#include <mach/gpio.h>
#include <mach/hardware.h>

#include <plat/gpio-cfg.h>
#include <plat/irqs.h>
*/

static struct i2c_client *my_i2c_client;

static const struct i2c_device_id my_i2c_dev_id[] = {
	{ "my_i2c_dev", 0 },
	{ }
};

static int my_i2c_drv_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{

    my_i2c_client = client;


    printk("my_i2c_ddrv_probe\n");

    return 0;
}

static int my_i2c_drv_remove(struct i2c_client *client)
{

    printk("my_i2c_dev_remove\n");

    return 0;
}

static struct i2c_driver my_i2c_drv = {
	.driver = {
		.name	= "jt_ts",
        .owner = THIS_MODULE,
	},
	.probe		= my_i2c_drv_probe,
	.remove		= my_i2c_drv_remove,
	.id_table	= my_i2c_dev_id,
};

static int __init my_i2c_drv_init(void)
{

	i2c_add_driver(&my_i2c_drv);

	return 0;
}

static void __exit my_i2c_drv_exit(void)
{

	i2c_del_driver(&my_i2c_drv);

	return;
}

module_init(my_i2c_drv_init);
module_exit(my_i2c_drv_exit);

MODULE_LICENSE("GPL");
