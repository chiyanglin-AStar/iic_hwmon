# I2C kernel module



## i2c board info and register
ref: http://shyuanliang.blogspot.com/2012/08/i2cregisterboardinfo-i2cboardinfo.html
    https://www.twblogs.net/a/5c2ba1adbd9eee17f85fbdc9
    
1. i2c_board_info, xxx device xxx address .

        static struct i2c_board_info __initdata ts02_i2c[] =
        {
                {
                        I2C_BOARD_INFO("lm75a", 0x49),
                },
                {
                        I2C_BOARD_INFO("ds1338", 0x68),
                }
        };

2.i2c_register_board_info(0, ts02_i2c, ARRAY_SIZE(ts02_i2c));
xxxx, xxx driver or  menuconfig xxxx.

then , you will see .
i2c /dev entries driver
rtc-ds1307 0-0068: rtc core: registered ds1338 as rtc0
rtc-ds1307 0-0068: 56 bytes nvram
i2c-gpio i2c-gpio.0: using pins 36 (SDA) and 37 (SCL)
lm75 0-0049: hwmon1: sensor 'lm75a'

    I2C_BOARD_INFO("ds1338", 0x68) need ¡§ds1338¡¨ this term same with id_table
    #define I2C_BOARD_INFO(dev_type, dev_addr) \
    .type = dev_type, .addr = (dev_addr)
        {
                I2C_BOARD_INFO("ds1338", 0x68),
        }
    or
        {
                .type        = "ds1338",
                .addr        = 0x68,
        }
