#pragma once
#include <stdint.h>
#include "../multiboot_utilities/multiboot_utils.h"

void pmm_init(multiboot2_mmap_entry_t*, uint32_t);
uint32_t pmm_alloc();
void pmm_free(uint32_t addr);


