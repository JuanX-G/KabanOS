#include <stdint.h>
#include "../../drivers/serial/serial.h"
#include "irq1.h"

void irq1_handler(void) {
	uint8_t scancode;

	__asm__ volatile("inb %1, %0" : "=a"(scancode) : "Nd"(0x60));
	if (scancode & 0x80)
		return;
	serial_write_char('K');
}
