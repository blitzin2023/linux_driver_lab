obj-m += klog_drv.o
APP_TARGET=klog_app

KERNEL=${DEV_KERNEL_PATH}

all:
	make -C ${KERNEL} M=$(PWD) modules
	${CROSS_COMPILE}gcc ${APP_TARGET}.c -o ${APP_TARGET}
clean:
	make -C ${KERNEL} M=$(PWD) clean
	@rm ${APP_TARGET} -f
