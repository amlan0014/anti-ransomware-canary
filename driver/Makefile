obj-m += ransomguard.o

KERNEL_DIR ?= /home/amlan/wsl-kernel
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNEL_DIR) M=$(PWD) clean
