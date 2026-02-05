#include "../../drivers/serial/serial.h"
#include "page_fault_handler.h"

void page_fault_handler(void) {
	serial_write_string("Page Fault Occured --- hanging!");
	kernel_hang();
}

void kernel_hang(void) {
	for (;;) {
		__asm__ volatile("hlt");
	}
}
