#!/bin/bash

function cmd()
{
	case $1 in
		clean)
			echo "Running command clean ..."
			rm .build -rf
			rm *.ko
			;;
		*)
			echo -e "\033[34m* Building ${1%%\.c} ...\033[0m"
			make MODULE=${1%%\.c} module
			;;
	esac
		
}

export BLITZ_KERNEL_PATH=${DEV_KERNEL_PATH}
echo -e "\033[34m【Using kernel: $BLITZ_KERNEL_PATH】\033[0m"

if [ -z ${BLITZ_KERNEL_PATH} ]; then
	echo " Error"
	exit	
fi

mkdir -p .build
cp Makefile .build

if [ -n "$1" ];
then
	cmd $1
else
	for drv in *.c;
	do
		echo -e "\033[34m* Building ${drv%%\.c} ...\033[0m"
		make MODULE=${drv%%\.c} module
	done
fi

echo -e "\033[34m- Done -\033[0m"

