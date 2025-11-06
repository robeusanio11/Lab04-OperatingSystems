#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int baseAddress;   // Starting address of the segment
    int segmentSize;   // Size of the segment
} Segment;

typedef struct {
    Segment* segments;
    int numSegments;
} SegmentTable;

int translateToPhysical(SegmentTable* table, int segmentNum, int offset) {
    if (segmentNum < 0 || segmentNum >= table->numSegments) {
        printf("Invalid segment number\n");
        return -1;
    }

    Segment segment = table->segments[segmentNum];

    if (offset < 0 || offset >= segment.segmentSize) {
        printf("Invalid offset\n");
        return -1;
    }

    return segment.baseAddress + offset;
}

int main() {
    // Example setup
    SegmentTable table;
    table.numSegments = 2;
    table.segments = (Segment*)malloc(table.numSegments * sizeof(Segment));
    table.segments[0] = (Segment){1000, 500};   // Code segment
    table.segments[1] = (Segment){2000, 1000};  // Data segment

    // Translate virtual address to physical address
    int physicalAddress = translateToPhysical(&table, 1, 100); // Data segment, offset 100
    printf("Physical address: %d\n", physicalAddress);

    free(table.segments);
    return 0;
}
