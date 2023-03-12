/*
ref : https://ithelp.ithome.com.tw/articles/10244815
*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/i2c.h>
#include <linux/string.h>
#include <linux/jiffies.h>
#include <linux/hwmon.h>
#include <linux/hwmon-sysfs.h>
#include <linux/err.h>
#include <linux/mutex.h>
#include <linux/of_device.h>
#include <linux/delay.h>
#include <linux/slab.h>

enum chips { iic_chip_data };

struct iic_chip {
	struct         i2c_client	*client;
	enum chips		 type;
	s16			       temp[3];	/* Register values */
	u16			       in[4];
};

static SENSOR_DEVICE_ATTR_RO(temp1_input, temp, 0);
static SENSOR_DEVICE_ATTR_RW(temp1_max_hyst, temp, 1);
static SENSOR_DEVICE_ATTR_RW(temp1_max, temp, 2);

static SENSOR_DEVICE_ATTR_RO(in1_input, adc, 0);
static SENSOR_DEVICE_ATTR_RO(in2_input, adc, 1);
static SENSOR_DEVICE_ATTR_RO(in3_input, adc, 2);
static SENSOR_DEVICE_ATTR_RO(in4_input, adc, 3);

static struct attribute *iic_chip_attr[] = {
  &sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_max_hyst.dev_attr.attr,
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in3_input.dev_attr.attr,
	&sensor_dev_attr_in4_input.dev_attr.attr,
	NULL
};
ATTRIBUTE_GROUPS(iic_chip_data);
static int iic_hwmon_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
    struct device *dev = &client->dev;
    struct i2c_adapter *adapter = client->adapter;
    struct iic_chip *data;
    struct device *hwmon_dev;
    const struct attribute_group **attr_groups = NULL;

    printk("printk:iic_hwmon_probe is being probed.\n");
    data = devm_kzalloc(dev, sizeof(struct iic_chip), GFP_KERNEL);
  	if (!data)
  		return -ENOMEM;
    hwmon_dev = devm_hwmon_device_register_with_groups(dev,
  							   client->name,
  							   data, attr_groups);
    return 0;
}

static int iic_hwmon_remove(struct i2c_client *client)
{
    printk("printk:iic_hwmon_probe is removings.\n");

    return 0;
}

static struct of_device_id iic_hwmon_id_tables [] = {
    { .compatible="nct6775",.data = (void *)iic_chip_data, },
    { }
};

MODULE_DEVICE_TABLE(of, iic_hwmon_id_tables);

static struct i2c_driver iic_hwmon_proto = {
    .class = I2C_CLASS_HWMON,
    .probe = iic_hwmon_probe,
    .remove = iic_hwmon_remove,
    .driver = {
    	.name = "iic_hwmon_proto",
	    .owner = THIS_MODULE,
	    .of_match_table = iic_hwmon_id_tables,
    },
};

module_i2c_driver(iic_hwmon_proto);

MODULE_AUTHOR("chiyang lin <chiyanglin@gmail.com>");
MODULE_DESCRIPTION("iic hwmon prototype driver");
MODULE_LICENSE("GPL");
