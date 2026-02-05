#include <stdint.h>
#include "../drivers/serial/serial.h"
#include "../multiboot_utilities/multiboot_utils.h"
#include "pmm.h"

#define FRAME_SIZE 4096

extern uint32_t kernel_end;   

static uint32_t *bitmap;     
static uint32_t total_frames;

static inline void set_frame(uint32_t frame)   { bitmap[frame / 32] |=  (1 << (frame % 32)); }
static inline void clear_frame(uint32_t frame) { bitmap[frame / 32] &= ~(1 << (frame % 32)); }
static inline int test_frame(uint32_t frame)   { return bitmap[frame / 32] & (1 << (frame % 32)); }

static void mark_frame_used(uint32_t addr) { set_frame(addr / FRAME_SIZE); }
static void mark_frame_free(uint32_t addr) { clear_frame(addr / FRAME_SIZE); }

void pmm_free(uint32_t addr) {
	mark_frame_free(addr);
}

uint32_t pmm_alloc() {
	for (uint32_t i = 0; i < total_frames; i++) {
		if (!test_frame(i)) {
			set_frame(i);
			return i * FRAME_SIZE;
		}
	}
	return 0;
}


void pmm_init(multiboot2_mmap_entry_t* mmap_list, uint32_t mmap_len) {
	bitmap = (uint32_t*)(((uint32_t)&kernel_end + FRAME_SIZE - 1) & ~(FRAME_SIZE - 1));
	for (uint32_t i = 0; i < total_frames / 32; i++)
		bitmap[i] = 0;

	for (uint32_t i = 0; i < 0x100000; i += FRAME_SIZE)
		set_frame(i / FRAME_SIZE);

	uint32_t bitmap_size = total_frames / 8;
	uint32_t bitmap_end =
		((uint32_t)bitmap + bitmap_size + FRAME_SIZE - 1) & ~(FRAME_SIZE - 1);

	for (uint32_t addr = (uint32_t)bitmap; addr < bitmap_end; addr += FRAME_SIZE)
		set_frame(addr / FRAME_SIZE);

	total_frames = 0x10000000 / FRAME_SIZE; 
	for (uint32_t i = 0; i < mmap_len; i++) {
		multiboot2_mmap_entry_t* entry = &mmap_list[i];
		if (entry->type == 1) {
			uint64_t start = entry->addr;
			uint64_t end   = entry->addr + entry->len;
			if (start < (uint32_t)&kernel_end)
				start = (uint32_t)&kernel_end;
			for (uint64_t addr = start; addr + FRAME_SIZE <= end; addr += FRAME_SIZE)
				pmm_free((uint32_t)addr);
		}
	}
	uint32_t offset = 0;
}

