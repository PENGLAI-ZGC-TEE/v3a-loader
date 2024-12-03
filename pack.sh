#!/bin/sh

FILE_BOOTROM=./build/bootrom/bootrom.bin
#FILE_UEFI=./bin/fw_payload.bin
FILE_UEFI=./bin/boot2.bin
FILE_OUT=./out/Image

mkdir -p out

if [ ! -f "$FILE_BOOTROM" ]; then
	echo "$FILE_BOOTROM does not exit!!"
fi

if [ ! -f "$FILE_UEFI" ]; then
	echo "$FILE_UEFI does not exit!!"
fi

if [ -f "$FILE_BOOTROM" -a -f "$FILE_UEFI" ]; then
	dd if=$FILE_BOOTROM of=$FILE_OUT
	dd if=$FILE_UEFI of=$FILE_OUT bs=1024k seek=3
	echo "pack success. $FILE_OUT"
fi
