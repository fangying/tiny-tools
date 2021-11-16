obj-m=readmmio.o
KDIR := /lib/modules/`uname -r`/build

all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm .*.cmd modules.order Module.symvers *.ko *.o *.mod.c *.mod
