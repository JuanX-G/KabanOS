[BITS 32]
section .text

global irq1

extern irq1_handler

irq1:
    cli
    pusha
    call irq1_handler
    popa
    mov al, 0x20
    out 0xA0, al
    out 0x20, al
    sti
    iret

