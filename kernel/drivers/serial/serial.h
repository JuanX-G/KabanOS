#pragma once
#include <stdint.h>

#define COM1 0x3F8

void serial_write_char(char c);
void serial_write_string(char* c);

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);

void early_print_hex(uint32_t n);
