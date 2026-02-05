#include <stdint.h>
#include "../../drivers/serial/serial.h"
#include "irq0.h"

volatile uint32_t ticks = 0;

void irq0_handler(void) {
	ticks++;
	if ((ticks % 100) == 0)
		serial_write_char('.');
}

