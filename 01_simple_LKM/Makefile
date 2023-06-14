PWD := $(shell pwd)
obj-m += mymodule.o

all:
	make ARCH=arm CROSS_COMPILE=$(CROSS) -C $(KERNEL) M=$(PWD) modules
clean:
	make ARCH=arm -C $(KERNEL) M=$(PWD) clean