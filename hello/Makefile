ds3231_drv.o:ds3231_drv.c
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) 

obj-m := ds3231_drv.o
