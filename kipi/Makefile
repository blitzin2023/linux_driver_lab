obj-m += kipi_drv.o
APP_TARGET=kipi_app

KERNEL=${DEV_KERNEL_PATH}

all:
	make -C $(KERNEL) M=$(PWD) modules KBUILD_EXTRA_SYMBOLS=$(PWD)/../../../git/intewellrtre/modules/rt_X/Module.symvers
	${CROSS_COMPILE}gcc $(APP_TARGET).c -o $(APP_TARGET)
clean:
	make -C $(KERNEL) M=$(PWD) clean
	@rm $(APP_TARGET) -f
