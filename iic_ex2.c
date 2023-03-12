#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/i2c.h>
#include <linux/err.h>
#include <linux/regmap.h>
#include <linux/slab.h>


static int my_i2c_drv_probe(struct i2c_client *client,
				  const struct i2c_device_id *id)
{
	printk("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	return 0;
}

static int my_i2c_drv_remove(struct i2c_client *client)
{
	printk("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
	return 0;
}

static const struct i2c_device_id my_dev_id_table[] = {
	{ "my_i2c_dev", 0 },
	{}
};

static int my_i2c_drv_detect(struct i2c_client *client,
		       struct i2c_board_info *info)
{
	/* 能運行到這裏, 表示該addr的設備是存在的
	 * 但是有些設備單憑地址無法分辨(A芯片的地址是0x50, B芯片的地址也是0x50)
	 * 還需要進一步讀寫I2C設備來分辨是哪款芯片
	 * detect就是用來進一步分辨這個芯片是哪一款，並且設置info->type
	 */

	printk("my_i2c_drv_detect: addr = 0x%x\n", client->addr);

	/* 進一步判斷是哪一款 */

	strlcpy(info->type, "my_i2c_dev", I2C_NAME_SIZE);
	return 0;
}

static const unsigned short addr_list[] = { 0x60, 0x50, I2C_CLIENT_END };

/* 1. 分配/設置i2c_driver */
static struct i2c_driver my_i2c_driver = {
	.class  = I2C_CLASS_HWMON, /* 表示去哪些適配器上找設備 */
	.driver	= {
		.name	= "my_i2c_dev",
		.owner	= THIS_MODULE,
	},
	.probe		= my_i2c_drv_probe,
	.remove		= my_i2c_drv_remove,
	.id_table	= my_dev_id_table,
	.detect     = my_i2c_drv_detect,  /* 用這個函數來檢測設備確實存在 */
	.address_list	= addr_list,   /* 這些設備的地址 */
};

static int my_i2c_drv_init(void)
{
	/* 2. 註冊i2c_driver */
	i2c_add_driver(&my_i2c_driver);

	return 0;
}

static void my_i2c_drv_exit(void)
{
	i2c_del_driver(&my_i2c_driver);
}


module_init(my_i2c_drv_init);
module_exit(my_i2c_drv_exit);
MODULE_LICENSE("GPL");
