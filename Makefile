SW_PATH = $(abspath .)
build_dir = $(realpath ./build)
BOOTROM = $(build_dir)/bootrom.bin

BOOTROM_PATH = $(SW_PATH)/bootrom

all: $(BOOTROM) 

bootrom: $(BOOTROM)


clean:
	$(MAKE) -C $(BOOTROM_PATH) clean
	rm -rf build
	rm -rf out

$(BOOTROM):
	$(MAKE) -C $(BOOTROM_PATH)
	mkdir -p build
	mkdir -p build/bootrom
	cp $(BOOTROM_PATH)/build/* build/bootrom/ -rf

pack:
	./pack.sh	

run:
	../../qemu/build/qemu-system-riscv64 -nographic  -M bosc-nh,aia=aplic-imsic  -m 4G -smp 1   -bios ./bootrom/build/bootrom.bin

debug:
	../../qemu/build/qemu-system-riscv64 -nographic  -M bosc-nh,aia=aplic-imsic  -m 4G -smp 1   -bios ./bootrom/build/bootrom.bin  -S -s
