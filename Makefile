SW_PATH = $(abspath .)
build_dir = $(realpath ./build)
BOOTROM = $(build_dir)/bootrom.bin
QEMU_TEST = $(build_dir)/qemu.bin

BOOTROM_PATH = $(SW_PATH)/bootrom
QEMU_TEST_PATH = $(SW_PATH)/qemu_test

all: $(BOOTROM) $(QEMU_TEST)

bootrom: $(BOOTROM)

qemu: $(QEMU_TEST)

clean:
	$(MAKE) -C $(BOOTROM_PATH) clean
	$(MAKE) -C $(QEMU_TEST_PATH) clean
	rm -rf build
	rm -rf out

$(BOOTROM):
	$(MAKE) -C $(BOOTROM_PATH)
	mkdir -p build
	mkdir -p build/bootrom
	cp $(BOOTROM_PATH)/build/* build/bootrom/ -rf

$(QEMU_TEST):
	$(MAKE) -C $(QEMU_TEST_PATH)
	mkdir -p build
	mkdir -p build/qemu
	cp $(QEMU_TEST_PATH)/build/* build/qemu/ -rf

pack:
	./pack.sh	

run:
	/home/guoyaxing/src/qemu-7.0.0/build/qemu-system-riscv64 -nographic \
	-machine virt -smp 2 -m 4G \
	-bios build/qemu/qemu_test.bin \

run-debug:
	/home/guoyaxing/src/qemu-7.0.0/build/qemu-system-riscv64 -nographic \
	-machine virt -smp 2 -m 4G \
	-bios build/qemu/qemu_test.bin \
	-S -s
