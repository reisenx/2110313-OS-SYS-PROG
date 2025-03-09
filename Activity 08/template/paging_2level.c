#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define FRAME_SIZE 256
#define FRAME_ENTRIES 128
#define PAGE_SIZE 256
#define PAGE_ENTRIES 16
#define OUTER_PAGE_ENTRIES 16

typedef struct PageTableEntry {
    uint16_t present : 1;
    uint16_t frame : 15;
} PageTableEntry;

PageTableEntry *page_table;
PageTableEntry *outer_page_table[OUTER_PAGE_ENTRIES];

uint8_t *physical_memory;
uint8_t frame_allocated[FRAME_ENTRIES]; // 0 = free, 1 = allocated

uint16_t translate_address(uint16_t logical_address) {

    // Assignment: get outer page number and page number from logical address
    uint8_t outer_page_number = ?;
    uint8_t page_number = ?;

    // Assignment: allocate inner page table
    if (outer_page_table? == ?) {
        // Inner page table not present, allocate an inner page table for it
        outer_page_table? = ?
		printf("Allocated inner page table for outer page %d\n", outer_page_number);
    }

    if (outer_page_table[outer_page_number][page_number].present == 0) {
        // Page not present, allocate a frame for it
        // For simplicity, just random a frame. Must fix this later.
        uint16_t frame_number;
        do {
            frame_number = rand() % FRAME_ENTRIES;
        } while (frame_allocated[frame_number]); // Keep trying until we find a free frame
    
        // Assignment: mark frame as allocated
        frame_allocated? = ?;

        // Assignment: fill in page table
        outer_page_table? = ?;
        outer_page_table? = ?;
    }

    // Assignment: construct physical address from frame number and offset
    uint16_t physical_address = ?;

    printf("Translate logical address 0x%X (outer page number 0x%X, page number 0x%X, offset 0x%X) to physical address 0x%X\n",
        logical_address, outer_page_number, page_number, logical_address & 0xFF, physical_address);

    return physical_address;
}

void read_from_memory(uint16_t logical_address, uint8_t *value) {
    uint16_t physical_address = translate_address(logical_address);
    *value = physical_memory[physical_address];
}

void write_to_memory(uint16_t logical_address, uint8_t value) {
    uint16_t physical_address = translate_address(logical_address);
    physical_memory[physical_address] = value;
}

// Print the current state of the page table
void print_page_tables() {
    printf("Outer Page Table:\n");
    printf("Outer Page | Inner Page Table\n");
    printf("---------------------------------------\n");

    // Print the outer page table state
    for (int i = 0; i < OUTER_PAGE_ENTRIES; i++) {
        printf("   0x%02X    | %s\n",
               i,
               outer_page_table[i] != NULL ? "address of inner page table for this entry (see below)" : "                  -");
    }

    // Print the inner page tables (only for allocated tables)
    printf("\nInner Page Tables (only allocated tables):\n");
    for (int i = 0; i < OUTER_PAGE_ENTRIES; i++) {
        if (outer_page_table[i] != NULL) {
            printf("\n--- Inner Page Table for Outer Page 0x%02X ---\n", i);
            printf("Inner Page | Present | Frame Number\n");
            printf("-----------------------------------\n");

            for (int j = 0; j < PAGE_ENTRIES; j++) {
                printf("   0x%02X    |    %d    |    0x%04X\n",
                       j,
                       outer_page_table[i][j].present,
                       outer_page_table[i][j].frame);
            }
        }
    }
}

int main() {
    // Allocate physical memory
    physical_memory = calloc(PAGE_ENTRIES, PAGE_SIZE);

    // Read and write to memory
    uint8_t value;
    write_to_memory(0x123, 0xA);
    read_from_memory(0x123, &value);
    printf("Value read from memory: 0x%02X\n", value);
    write_to_memory(0x1234, 0xB);
    read_from_memory(0x1234, &value);
    printf("Value read from memory: 0x%02X\n", value);
	write_to_memory(0xFF12, 0xC);
    read_from_memory(0xFF12, &value);
    printf("Value read from memory: 0x%02X\n", value);

   // Print page table
   print_page_tables();

   // Calculate total size of outer page table and inner page tables
    size_t page_table_size = 0;
    for (int i = 0; i < OUTER_PAGE_ENTRIES; i++) {
        if (outer_page_table[i] != NULL) {
            page_table_size += PAGE_ENTRIES * sizeof(PageTableEntry);
        }
    }

    printf("Outer page table size: %zu bytes\n", sizeof(outer_page_table));
    printf("Inner page table size: %zu bytes\n", page_table_size);
    printf("Total page table size: %zu bytes\n", sizeof(outer_page_table)+page_table_size);

    return(0);
}
