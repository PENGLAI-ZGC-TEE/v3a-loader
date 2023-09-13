GNU = riscv64-unknown-linux-gnu-

CC = $(GNU)gcc
LD = $(GNU)ld
RISCV_COPY = $(GNU)objcopy
RISCV_COPY_FLAGS = --set-section-flags .bss=alloc,contents --set-section-flags .sbss=alloc,contents -O binary
RISCV_DUMP = $(GNU)objdump

BUILD_DIR = build
SRC_DIR = $(abspath .)
ENTRY_DIR = $(SRC_DIR)/entry
UART_DIR = $(SRC_DIR)/uart

COPS = -g -O0 -Wall -nostdlib -Iinclude -I../include -mcmodel=medany -mabi=lp64 -march=rv64imafdc -fno-PIE -fomit-frame-pointer -Wno-builtin-declaration-mismatch

C_FILES = $(wildcard $(UART_DIR)/*.c)
ASM_FILES = $(wildcard $(ENTRY_DIR)/*.S)
OBJ_FILES = $(ASM_FILES:$(ENTRY_DIR)/%.S=$(BUILD_DIR)/%_s.o)
OBJ_FILES += $(C_FILES:$(UART_DIR)/%.c=$(BUILD_DIR)/%_c.o)

default: $(OBJ_FILES)
	$(LD) -T $(SRC_DIR)/qemu_test.ld -o $(BUILD_DIR)/qemu_test.elf $(OBJ_FILES) -Map $(BUILD_DIR)/qemt_test.map
	$(RISCV_COPY) $(BUILD_DIR)/qemu_test.elf -O binary $(BUILD_DIR)/qemu_test.bin
	rm -rf $(BUILD_DIR)/*.o

$(BUILD_DIR)/%_s.o: $(ENTRY_DIR)/%.S
	mkdir -p $(BUILD_DIR)
	$(CC) $(COPS) -c $< -o $@

$(BUILD_DIR)/%_c.o: $(UART_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(COPS) -c $< -o $@

clean:
	rm -rf build
	
