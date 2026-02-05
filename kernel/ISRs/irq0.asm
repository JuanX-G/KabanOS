[BITS 32]
section .text

global irq0

extern irq0_handler

irq0:
    cli
    pusha
    call irq0_handler
    popa
    mov al, 0x20
    out 0x20, al

    sti
    iret

