
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
    struct Block* prev; 
    bool is_mmaped; 
    
} Block; 

/* ------ Fit algorithms ----- */ 

// Find the first block that fits the required size 
Block* first_fit(Block** free_list, size_t size); 

/* --------- Utils --------- */ 

// Returns a pointer to the usable memory section after the block header
// given a pointer to the block 
void* get_usable_memory(Block* block_header);  
// Returns a pointer to the block header given a pointer to the usable memory section
Block* get_block_memory(void* memory);  

// Split a block, adding the new block to the free list of size size_to_split 
bool is_splittable(Block* block, size_t size_to_split);  
Block* split_block(Block* block, size_t size_to_split);  

// Merge all blocks in the free list 
void merge_blocks(Block** free_list);  




// Remove and add a block to the free list 
void remove_block(Block** free_list, Block* block); 
void add_block(Block** free_list, Block* block);  


#endif
