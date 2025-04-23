#include <uart.h>
#include <asm/mmio.h>
#include <print.h>
#include <pll.h>

#define FLASH0_BASE              0x2000000
#define BOOTROM_FLASH0_BASE      FLASH0_BASE  // 0x200'0000

#define FLASH1_BASE              0x4200000
#define OPENSBI_FLASH1_BASE      FLASH1_BASE  // 0x420'0000
#define OPTEE_FLASH1_BASE       (OPENSBI_FLASH1_BASE + OPENSBI_SIZE)
#define LINUX_FLASH1_BASE       (OPTEE_FLASH1_BASE + OPTEE_SIZE)

#define DDR_BASE              0x80000000
#define OPENSBI_DDR_BASE      DDR_BASE  // 0x8000'0000
#define OPTEE_DDR_BASE       (OPENSBI_DDR_BASE + 0x1000000) // 0x8100'0000
#define LINUX_DDR_BASE       (OPTEE_DDR_BASE + 0x1000000)   // 0x8200'0000

#define MACRO(j) ramStart[i + j] = romStart[i + j]
#define MACRO4(j) MACRO(j); MACRO(j + 1); MACRO(j + 2); MACRO(j + 3);
typedef unsigned long long   uint64_t;

void flash_cpy(void *src, void *dst, uint64_t size)
{
    uint64_t *romStart = (uint64_t *)src;
    uint64_t *ramStart = (uint64_t *)dst;

    for (uint64_t i = 0; i < size; i++)
    {
        ramStart[i] = romStart[i];
    }
}

void _main(void)
{
    writel(0xb0014, 0x15501003);

    my_print("starting copy from flash to ram...\r\n");

    /* copy OpenSBI */
    flash_cpy((void *)OPENSBI_FLASH1_BASE, (void *)OPENSBI_DDR_BASE, (OPENSBI_SIZE / 8));
    my_print("copy OpenSBI done. from: 0x%lx to 0x%lx, size: %lx\r\n", OPENSBI_FLASH1_BASE, OPENSBI_DDR_BASE, OPENSBI_SIZE);

    /* copy OP-TEE */
    flash_cpy((void *)OPTEE_FLASH1_BASE, (void *)OPTEE_DDR_BASE, (OPTEE_SIZE / 8));
    my_print("copy OP-TEE done. from: 0x%lx to 0x%lx, size: %lx\r\n", OPTEE_FLASH1_BASE, OPTEE_DDR_BASE, OPTEE_SIZE);

    /* copy Linux */
    flash_cpy((void *)LINUX_FLASH1_BASE, (void *)LINUX_DDR_BASE, (LINUX_SIZE / 8));
    my_print("copy Linux done. from: 0x%lx to 0x%lx, size: %lx\r\n", LINUX_FLASH1_BASE, LINUX_DDR_BASE, LINUX_SIZE);

    my_print("all copy done\r\n");

    my_print("\r\n");
#ifdef CORE_1_G
    my_print("core frq 1G \r\n");
#endif
#ifdef CORE_1_5G
    my_print("core frq 1.5G \r\n");
#endif
#ifdef DDR_1600
    my_print("ddr frq 1600 \r\n");
#endif
#ifdef DDR_2100
    my_print("ddr frq 2132 \r\n");
#endif
#ifdef DDR_2400
    my_print("ddr frq 2400 \r\n");
#endif
    writel(0x38000004, 1);
    asm volatile("fence.i");
    ((void (*)())DDR_BASE)();
    while (1)
    {
    };
}
