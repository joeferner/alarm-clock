#!/bin/bash -e

DIR=$(cd $(dirname $0) && pwd)
KERNEL_SRC=${DIR}/linux
cd ${DIR}

if [ $# -ne 2 ]; then
    echo "Usage: $0 <pi address> <cores>"
    exit 1
fi

PIADDR=$1
CORES=$2

export PATH=${DIR}/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin/:${PATH}

FIRMWARE_HASH=$(ssh pi@${PIADDR} "zgrep \"* firmware as of\" /usr/share/doc/raspberrypi-bootloader/changelog.Debian.gz | head -1 | awk '{ print \$5 }'")
KERNEL_HASH=$(ssh pi@${PIADDR} "wget https://raw.github.com/raspberrypi/firmware/${FIRMWARE_HASH}/extra/git_hash -O -")
KERNEL_RELEASE=$(ssh pi@${PIADDR} "uname -r")
ssh pi@${PIADDR} "sudo modprobe configs && zcat /proc/config.gz" > ${KERNEL_SRC}/.config

echo "FIRMWARE_HASH=$FIRMWARE_HASH"
echo "KERNEL_HASH=$KERNEL_HASH"
echo "KERNEL_RELEASE=$KERNEL_RELEASE"

cd ${KERNEL_SRC}
KERNEL=kernel7

make -j${CORES} ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- bcm2709_defconfig
make -j${CORES} ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- zImage modules dtbs

scp ./drivers/staging/fbtft/*.ko pi@${PIADDR}:/lib/modules/${KERNEL_RELEASE}/kernel/drivers/staging/fbtft/

