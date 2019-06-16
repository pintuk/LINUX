
EXTRA_CFLAGS	+= -I$(shell pwd)

obj-m := pintty.o
ttyPin-objs := pintty_init.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

