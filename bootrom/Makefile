GNU = riscv64-linux-gnu-

CC = $(GNU)gcc
LD = $(GNU)ld
RISCV_COPY = $(GNU)objcopy
RISCV_COPY_FLAGS = --set-section-flags .bss=alloc,contents --set-section-flags .sbss=alloc,contents -O binary
RISCV_DUMP = $(GNU)objdump

BUILD_DIR = build
BOOTROM_DIR = $(abspath .)
BOOTROM_ENTRY_DIR = $(BOOTROM_DIR)/entry
BOOTROM_DRIVER_DIR = $(BOOTROM_DIR)/driver
BOOTROM_SRC_DIR = $(BOOTROM_DIR)/src
BUILD_DIR_DRIVER = $(BUILD_DIR)/driver
BUILD_DIR_SRC = $(BUILD_DIR)/src

COPS = -g -O1 -Wall -nostdlib -Iinclude -I../include -mcmodel=medany -mabi=lp64 -march=rv64gcv -fno-PIE -fomit-frame-pointer -Wno-builtin-declaration-mismatch

DRIVER_FILES += $(wildcard $(BOOTROM_DRIVER_DIR)/uart.c)
DRIVER_FILES += $(wildcard $(BOOTROM_DRIVER_DIR)/soc_cru.c)
ifeq ($(shell grep -q '^ *# *define *DDR_1600' ../include/pll.h && echo "YES"), YES)
	DRIVER_FILES += $(wildcard $(BOOTROM_DRIVER_DIR)/ddrc16.c)
endif
ifeq ($(shell grep -q '^ *# *define *DDR_2100' ../include/pll.h && echo "YES"), YES)
	DRIVER_FILES += $(wildcard $(BOOTROM_DRIVER_DIR)/ddrc21.c)
endif
ifeq ($(shell grep -q '^ *# *define *DDR_2400' ../include/pll.h && echo "YES"), YES)
	DRIVER_FILES += $(wildcard $(BOOTROM_DRIVER_DIR)/ddrc24.c)
endif 
SRC_FILES += $(wildcard $(BOOTROM_SRC_DIR)/*.c)
ASM_FILES = $(wildcard $(BOOTROM_ENTRY_DIR)/*.S)
OBJ_FILES = $(ASM_FILES:$(BOOTROM_ENTRY_DIR)/%.S=$(BUILD_DIR)/%_s.o)
OBJ_FILES += $(DRIVER_FILES:$(BOOTROM_DRIVER_DIR)/%.c=$(BUILD_DIR_DRIVER)/%_c.o)
OBJ_FILES += $(SRC_FILES:$(BOOTROM_SRC_DIR)/%.c=$(BUILD_DIR_SRC)/%_c.o)

default: $(OBJ_FILES)
	$(LD)  -T $(BOOTROM_DIR)/bootrom.ld -o $(BUILD_DIR)/bootrom.elf $(OBJ_FILES) -Map $(BUILD_DIR)/bootrom.map
	$(RISCV_COPY) $(BUILD_DIR)/bootrom.elf -O binary $(BUILD_DIR)/bootrom.bin
	rm $(BUILD_DIR)/*.o
	
$(BUILD_DIR)/%_s.o: $(BOOTROM_ENTRY_DIR)/%.S
	mkdir -p $(BUILD_DIR)
	$(CC) $(COPS) -c $< -o $@

$(BUILD_DIR_DRIVER)/%_c.o: $(BOOTROM_DRIVER_DIR)/%.c
	mkdir -p $(BUILD_DIR_DRIVER)
	$(CC) $(COPS) -c $< -o $@
$(BUILD_DIR_SRC)/%_c.o: $(BOOTROM_SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR_SRC)
	$(CC) $(COPS) -c $< -o $@

clean:
	rm -rf build
lst:
	$(GNU)objdump -S build/bootrom.elf > build/bootrom.lst
