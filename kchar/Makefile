obj-m += p_drv.o
APP=p_app

KERNEL=${DEV_KERNEL_PATH}

all:
	make -C $(KERNEL) -o ./output M=$(PWD) modules
	${CROSS_COMPILE}gcc ${APP}.c -o app
clean:
	make -C $(KERNEL) M=$(PWD) clean
	rm output -rf
	rm app -rf
