SW_PATH = $(abspath .)
build_dir = $(realpath ./build)
BOOTROM = $(build_dir)/bootrom.bin
BOOTROM_PATH = $(SW_PATH)/bootrom
BOOT2 = $(build_dir)/boot2.bin
BOOT2_PATH = $(SW_PATH)/boot2

all: $(BOOT2) $(BOOTROM) 

boot2: $(BOOT2)
bootrom: $(BOOTROM)

clean:
	$(MAKE) -C $(BOOT2_PATH) clean
	$(MAKE) -C $(BOOTROM_PATH) clean
	rm -rf build
	rm -rf out

$(BOOT2):
	$(MAKE) -C $(BOOT2_PATH)
	mkdir -p build
	mkdir -p build/boot2
	cp $(BOOT2_PATH)/build/* build/boot2/ -rf

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
