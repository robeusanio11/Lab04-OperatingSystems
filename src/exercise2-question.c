#include <stdio.h>
#include <stdlib.h>

typedef struct FreeBlock {
    int size;                    
    int start;                   
    struct FreeBlock* next;      
} FreeBlock;

typedef struct {
    FreeBlock* head;
} FreeList;

FreeBlock* createBlock(int start, int size) {
    FreeBlock* block = (FreeBlock*)malloc(sizeof(FreeBlock));
    block->start = start;
    block->size = size;
    block->next = NULL;
    return block;
}

void initFreeList(FreeList* list) {
    list->head = NULL;
}

void addFreeBlock(FreeList* list, int start, int size) {
    FreeBlock* newBlock = createBlock(start, size);

    if (list->head == NULL || start < list->head->start) {
        newBlock->next = list->head;
        list->head = newBlock;
    } 
    else {
        FreeBlock* temp = list->head;

        while (temp->next != NULL && temp->next->start < start) {
            temp = temp->next;
        }
        newBlock->next = temp->next;
        temp->next = newBlock;
    }

    printf("Added free block: start=%d size=%d\n", start, size);
}

void mergeBlocks(FreeList* list) {
    if (list->head == NULL) return;

    FreeBlock* temp = list->head;

    while (temp->next != NULL) {
        if (temp->start + temp->size == temp->next->start) {
            temp->size += temp->next->size;
            FreeBlock* toDelete = temp->next;
            temp->next = temp->next->next;
            free(toDelete);
        } else {
            temp = temp->next;
        }
    }
}

void allocateBlock(FreeList* list, int requestSize) {
    FreeBlock* temp = list->head;
    FreeBlock* prev = NULL;

    while (temp != NULL) {
        if (temp->size >= requestSize) {
            printf("Allocating %d bytes from block starting at %d\n",
                   requestSize, temp->start);

            if (temp->size == requestSize) {
                if (prev == NULL) list->head = temp->next;
                else prev->next = temp->next;

                free(temp);
            }
            else {
                temp->start += requestSize;
                temp->size -= requestSize;
            }
            return;
        }

        prev = temp;
        temp = temp->next;
    }

    printf("Allocation failed: no block large enough\n");
}

void freeBlock(FreeList* list, int start, int size) {
    addFreeBlock(list, start, size);
    mergeBlocks(list);
}

void printFreeList(FreeList* list) {
    FreeBlock* temp = list->head;
    printf("Free List:\n");

    while (temp != NULL) {
        printf("Start: %d, Size: %d\n", temp->start, temp->size);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    FreeList freeList;
    initFreeList(&freeList);

    addFreeBlock(&freeList, 0, 100);
    addFreeBlock(&freeList, 200, 300);
    addFreeBlock(&freeList, 600, 150);

    printFreeList(&freeList);

    allocateBlock(&freeList, 60);
    printFreeList(&freeList);

    freeBlock(&freeList, 100, 100);
    printFreeList(&freeList);

    return 0;
}
