mydriver.o: mydriver.c
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD)

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) 

obj-m := mydriver.o
