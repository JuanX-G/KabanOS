#include <stdint.h>
#include "multiboot_utils.h"
void parse_multiboot2(uint32_t addr, multiboot2_full_t *full_info) {
	multiboot2_info_t *mb = (multiboot2_info_t *)addr;
	uint8_t *end = (uint8_t *)mb + mb->total_size;

	for (multiboot2_tag_t *tag =
			(multiboot2_tag_t *)(mb + 1);
			tag->type != 0 && (uint8_t *)tag < end;
			tag = (multiboot2_tag_t *)((uint8_t *)tag +
				((tag->size + 7) & ~7))) {
		switch (tag->type) {
			case 4:
				multiboot2_tag_basic_meminfo_t *mem = (multiboot2_tag_basic_meminfo_t *)tag;
				full_info->meminfo = *mem;
				break;
			case 6:
				multiboot2_tag_mmap_t *mmap = (multiboot2_tag_mmap_t *)tag;

				uint8_t *entry_ptr = (uint8_t *)mmap + sizeof(multiboot2_tag_mmap_t);

				uint8_t *entry_end = (uint8_t *)tag + tag->size;

				for (uint32_t i = 0; entry_ptr < entry_end && i < 128; i++ ) {
					multiboot2_mmap_entry_t *entry = (multiboot2_mmap_entry_t *)entry_ptr;

					__builtin_memcpy(&full_info->mmap_entries[i].len, &entry->len, sizeof(uint64_t));
					__builtin_memcpy(&full_info->mmap_entries[i].addr, &entry->addr, sizeof(uint64_t));
					__builtin_memcpy(&full_info->mmap_entries[i].type, &entry->type, sizeof(uint32_t));
					__builtin_memcpy(&full_info->mmap_entries[i].zero, &entry->zero, sizeof(uint32_t));
					entry_ptr += mmap->entry_size;
				}
				break;
		}

	}


}
