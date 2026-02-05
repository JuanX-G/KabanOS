section .bss
align 4096
page_directory:
    resb 4096

align 4096
page_tables:
    resb 4096 * 16

section .text
global paging_enable
paging_enable:
	pusha
    mov ecx, 1024
    xor eax, eax
    mov edi, page_directory
    rep stosd

    mov edi, page_tables       
    xor ebx, ebx              
    mov ecx, 1024 * 16         

.map_pages_loop:
    mov eax, ebx
    or eax, 3                
    stosd
    add ebx, 4096
    loop .map_pages_loop

    mov edi, page_directory    
    mov eax, page_tables      
    mov ecx, 16

.fill_directory_loop:
    push eax                    
    or eax, 3                   ; Present + RW
    stosd                      
    pop eax                   
    add eax, 4096               ; Move to next table address
    loop .fill_directory_loop

    mov eax, page_directory
    mov cr3, eax
    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax
    popa
    ret
