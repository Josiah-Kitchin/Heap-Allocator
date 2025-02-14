
#ifndef BLOCK_H
#define BLOCK_H

#include <stdio.h> 
#include <stdbool.h> 

typedef struct Block { 
    /* Block metadata for allocated memory 
     * The block will be stored as a header in the allocated memory, 
     * its size will be the number of bytes of usable memory. 
     * 
     * Next is used when the block is transfered to the free list, meaning 
     * the memory is no longer in use and next points to the next 
     * free block of memory 
     */ 
    size_t size; 
    struct Block* next; 
} Block; 

Block* get_free_block(Block** free_list, size_t size); 

#endif
