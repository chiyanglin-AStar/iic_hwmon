#obj-$(CONFIG_SENSORS_AD7418)	+= ad7418.o
#obj-m += iic_hwmon.o
#obj-m += iic_arduino.o

#obj-m += lm75.o

obj-m += iic_ex3.o

#KDIR=/usr/src/linux-4.16.8
KDIR=/lib/modules/$(shell uname -r)/build

all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	make -C $(KDIR) M=$(PWD) clean
