obj-m += myproc.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

load: hello.ko
	sudo insmod hello.ko

unload:
	sudo rmmod hello
