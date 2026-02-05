#pragma once
#include <stdint.h>

typedef struct multiboot2_tag {
    uint32_t type;
    uint32_t size;
} __attribute__((packed)) multiboot2_tag_t;

typedef struct {
    uint32_t type;
    uint32_t size;
    uint32_t mem_lower;
    uint32_t mem_upper;
} __attribute__((packed)) multiboot2_tag_basic_meminfo_t;

typedef struct {
    uint32_t type;
    uint32_t size;
    uint32_t entry_size;
    uint32_t entry_version;
} __attribute__((packed)) multiboot2_tag_mmap_t;

typedef struct {
    uint64_t addr;
    uint64_t len;
    uint32_t type;
    uint32_t zero;
} __attribute__((packed)) multiboot2_mmap_entry_t;

typedef struct {
    uint32_t type;
    uint32_t size;
    char string[];
} __attribute__((packed)) multiboot2_tag_bootloader_t;

typedef struct {
    uint32_t type;
    uint32_t size;
    char string[];
} __attribute__((packed)) multiboot2_tag_cmdline_t;

typedef struct {
    uint32_t total_size;
    uint32_t reserved;
} __attribute__((packed)) multiboot2_info_t;

typedef struct {
    multiboot2_tag_basic_meminfo_t meminfo;
    multiboot2_mmap_entry_t mmap_entries[128];
} multiboot2_full_t;

void parse_multiboot2(uint32_t addr, multiboot2_full_t *out);

