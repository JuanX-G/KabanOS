global _start

extern kernel_main
extern gdt_flush
extern paging_enable


section .multiboot
align 8

header_start:
dd 0xe85250d6        
dd 0                
	dd header_end - header_start
	dd -(0xe85250d6 + 0 + (header_end - header_start))

	dw 0
	dw 0
	dd 8

header_end:
section .bss
align 16
	stack_bottom: resb 16384      
	stack_top equ stack_bottom + 16384


section .text
_start:
	mov dx, 0x3F8 + 1
	mov al, 0
	out dx, al

	mov dx, 0x3F8 + 3
	mov al, 0x80
	out dx, al

	mov dx, 0x3F8
	mov al, 3
	out dx, al

	mov dx, 0x3F8 + 1
	mov al, 0
	out dx, al

	mov dx, 0x3F8 + 3
	mov al, 3
	out dx, al
	mov dx, 0x3F8
	mov al, 'A'
	out dx, al

	mov esp, stack_top

	call gdt_flush

	push ebx
	call kernel_main

.hang:
	cli
	hlt
	jmp .hang

