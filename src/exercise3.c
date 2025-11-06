#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 256
#define NUM_PAGES 4
#define NUM_FRAMES 4

typedef struct {
    int frameNumber; // Maps page number to frame number
} PageTableEntry;

typedef struct {
    PageTableEntry* entries;
    int numEntries;
} PageTable;

int translateToPhysical(PageTable* pt, int pageNum, int offset) {
    if (pageNum < 0 || pageNum >= pt->numEntries) {
        printf("Page fault: invalid page number\n");
        return -1;
    }

    int frameNum = pt->entries[pageNum].frameNumber;
    return frameNum * PAGE_SIZE + offset;
}

int main() {
    PageTable pt;
    pt.numEntries = NUM_PAGES;
    pt.entries = (PageTableEntry*)malloc(pt.numEntries * sizeof(PageTableEntry));

    // Example: Mapping page 0 to frame 2, page 1 to frame 1
    pt.entries[0] = (PageTableEntry){2}; // Page 0 -> Frame 2
    pt.entries[1] = (PageTableEntry){1}; // Page 1 -> Frame 1

    int physicalAddress = translateToPhysical(&pt, 1, 50); // Page 1, offset 50
    printf("Physical address: %d\n", physicalAddress);

    free(pt.entries);
    return 0;
}
