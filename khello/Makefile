obj-m += $(MODULE).o

SRC=$(PWD)
BUILD=$(PWD)/.build

all:
	@./build.sh
direct:
	make -C $(BLITZ_KERNEL_PATH) M=$(PWD) modules
module:
	make -C $(BLITZ_KERNEL_PATH) M=$(BUILD) src=$(PWD) modules
	@cp $(PWD)/.build/*.ko .
clean:
	make -C $(BLITZ_KERNEL_PATH) M=$(PWD) clean
	@rm *.ko -f
	@rm .build -rf
