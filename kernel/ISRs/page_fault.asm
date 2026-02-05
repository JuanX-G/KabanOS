global isr14
extern page_fault_handler

isr14:
    cli                 
    pusha              
    call page_fault_handler
    popa
    add esp, 4
    iret

