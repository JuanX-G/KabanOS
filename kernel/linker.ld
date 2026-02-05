ENTRY(_start)

SECTIONS
{
    . = 0x8000;   /* load kernel at 32 KB */
    .multiboot : { *(.multiboot) }
    .text      : { *(.text*) }
    .rodata    : { *(.rodata*) }
    .data      : { *(.data*) }
    .bss       : { *(.bss*) }
    kernel_end = .;
}

