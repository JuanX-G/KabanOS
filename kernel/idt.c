#include <stdint.h>
#include "idt.h"

void set_idt_entry(int n, void (*handler)()) {
    uintptr_t addr = (uintptr_t)handler;
    idt[n].offset_low = addr & 0xFFFF;
    idt[n].selector = 0x08;   // code segment
    idt[n].zero = 0;
    idt[n].type_attr = 0x8E;  // interrupt gate
    idt[n].offset_high = (addr >> 16) & 0xFFFF;
}

void idt_load() {
    idt_p.limit = sizeof(idt) - 1;
    idt_p.base = (uint32_t)&idt;
    __asm__ volatile("lidt (%0)" : : "r"(&idt_p));
}

extern void isr_default(void);
extern void isr14(void);
extern void irq0(void);
extern void irq1(void);

void idt_init(void) {
    for (int i = 0; i < 255; i++)
	    set_idt_entry(i, isr_default);

    set_idt_entry(14, isr14);
    set_idt_entry(32, irq0);
    set_idt_entry(33, irq1);

    idt_load();
}

