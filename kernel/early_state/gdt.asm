global gdt_flush

section .data
gdt_start:

dq 0x0000000000000000   ; null

dq 0x00CF9A000000FFFF   ; code segment
dq 0x00CF92000000FFFF   ; data segment

gdt_end:

gdt_descriptor:
dw gdt_end - gdt_start - 1
dd gdt_start

section .text
gdt_flush:
    lgdt [gdt_descriptor]

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    jmp 0x08:.flush

.flush:
    ret

