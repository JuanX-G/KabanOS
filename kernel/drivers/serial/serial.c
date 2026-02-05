#include <stdint.h>
#include "serial.h"

void serial_write_char(char c) {
	while (!(inb(COM1 + 5) & 0x20));
	outb(COM1, c);
}

void serial_write_string(char* c) {
	for (int i = 0; c[i] != '\0'; i++)
		serial_write_char(c[i]);
}

void outb(uint16_t port, uint8_t val) {
	__asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

uint8_t inb(uint16_t port) {
	uint8_t ret;
	__asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
	return ret;
}

void early_print_hex(uint32_t n) {
	char *chars = "0123456789ABCDEF";
	for (int i = 28; i >= 0; i -= 4) {
		serial_write_char(chars[(n >> i) & 0xF]);
	}
}
