#include "drivers/serial/serial.h"
#include "drivers/pic/pic.h"
#include "mem/pmm.h"
// #include "mem/adv_paging.h"
#include "multiboot_utilities/multiboot_utils.h"
#include <stddef.h>

extern void idt_init(void);
extern void paging_enable(void);

void print_hex(uint32_t n);
static multiboot2_full_t out_info;

void kernel_main(uint32_t multiboot_info) {
	volatile char* vga = (volatile char*)0xB8000;
	idt_init();               
	serial_write_string("loading KabanOS...\n");
	serial_write_string("IDT installed\n");
	pic_remap();
	pit_init();

	paging_enable();
	parse_multiboot2(multiboot_info, &out_info);
	serial_write_string("multiboot parsed\n");
	vga[0] = 'O';
	vga[1] = 0x0F;
	vga[2] = 'K';
	vga[3] = 0x0F;

	pmm_init(out_info.mmap_entries, sizeof(out_info.mmap_entries)/sizeof(out_info.mmap_entries[0]));
	serial_write_string("pmm initliazed\n");

	__asm__ volatile("sti");
	uint32_t frame1 = pmm_alloc();
	uint32_t frame2 = pmm_alloc();
	uint32_t frame3 = pmm_alloc();

	early_print_hex(frame1);
	early_print_hex(frame2);
	early_print_hex(frame3);

	for (;;);

}

