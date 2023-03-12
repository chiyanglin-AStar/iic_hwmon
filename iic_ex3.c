#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/i2c.h>
#include <linux/err.h>
#include <linux/slab.h>

static struct i2c_board_info my_i2c_dev_info = {
    I2C_BOARD_INFO("my_i2c_dev", 0x50), /* 這個名字和地址很重要 */
};

static struct i2c_client *my_i2c_client;

static int i2c_dev_init(void)
{
    struct i2c_adapter *i2c_adap;
    printk(" iic dev init\n");
    i2c_adap = i2c_get_adapter(0); /* 得到i2c設備器，i2c設備在哪條總線上 */
    my_i2c_client = i2c_new_client_device(i2c_adap, &my_i2c_dev_info);
    //i2c_new_device(i2c_adap, &my_i2c_dev_info);
    i2c_put_adapter(i2c_adap);

    return 0;
}

static void i2c_dev_exit(void)
{
    i2c_unregister_device(my_i2c_client);
}

module_init(i2c_dev_init);
module_exit(i2c_dev_exit);
MODULE_LICENSE("GPL");
