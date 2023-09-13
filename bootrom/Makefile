GNU = riscv64-unknown-linux-gnu-

CC = $(GNU)gcc
LD = $(GNU)ld
RISCV_COPY = $(GNU)objcopy
RISCV_COPY_FLAGS = --set-section-flags .bss=alloc,contents --set-section-flags .sbss=alloc,contents -O binary
RISCV_DUMP = $(GNU)objdump

BUILD_DIR = build
BOOTROM_SRC_DIR = $(abspath .)
BOOTROM_ENTRY_DIR = $(BOOTROM_SRC_DIR)/entry
BOOTROM_UART_DIR = $(BOOTROM_SRC_DIR)/uart

COPS = -g -O0 -Wall -nostdlib -Iinclude -I../include -mcmodel=medany -mabi=lp64 -march=rv64imafdc -fno-PIE -fomit-frame-pointer -Wno-builtin-declaration-mismatch

C_FILES = $(wildcard $(BOOTROM_UART_DIR)/*.c)
ASM_FILES = $(wildcard $(BOOTROM_ENTRY_DIR)/*.S)
OBJ_FILES = $(ASM_FILES:$(BOOTROM_ENTRY_DIR)/%.S=$(BUILD_DIR)/%_s.o)
OBJ_FILES += $(C_FILES:$(BOOTROM_UART_DIR)/%.c=$(BUILD_DIR)/%_c.o)

default: $(OBJ_FILES)
	$(LD) -T $(BOOTROM_SRC_DIR)/bootrom.ld -o $(BUILD_DIR)/bootrom.elf $(OBJ_FILES) -Map $(BUILD_DIR)/bootrom.map
	$(RISCV_COPY) $(BUILD_DIR)/bootrom.elf -O binary $(BUILD_DIR)/bootrom.bin
	rm $(BUILD_DIR)/*.o
	
$(BUILD_DIR)/%_s.o: $(BOOTROM_ENTRY_DIR)/%.S
	mkdir -p $(BUILD_DIR)
	$(CC) $(COPS) -c $< -o $@

$(BUILD_DIR)/%_c.o: $(BOOTROM_UART_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(COPS) -c $< -o $@

clean:
	rm -rf build
	
