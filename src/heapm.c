

#include "heapm.h"
#include "block.h"
#include "bucket.h"
#include <stdint.h> 
#include <sys/mman.h> 
#include <unistd.h> 


#define NUM_BUCKETS 3
#define LARGE_BLOCK_SIZE 196000 

static Bucket buckets[NUM_BUCKETS] = {
    {NULL, 64}, 
    {NULL, 128},
    {NULL, -1}
};

static size_t align_size(size_t size) 
{ 
    /* Aligin a size to fit in the block header 
     * Rounds the size to the next multiple of sizeof(Block)
     */ 
    return (size + sizeof(Block) - 1) & ~(sizeof(Block) - 1); 
}

static Block* allocate_block(size_t size) { 
    /* Allocates memory via a syscall 
     * Stores the block metadata at the beggining of memory and the usable
     * memory after
     * Parameters: 
     *     size: Number of bytes requested to be allocated 
     * Returns: 
     *     A pointer to the block metadata, with block->size usable memory after 
     *     the block metadata
     *     NULL if the allocation fails 
     */ 
    Block* block_memory; 
    if (size >= LARGE_BLOCK_SIZE)
    {
        block_memory = mmap(NULL, size + sizeof(Block), 
                                   PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if (block_memory == MAP_FAILED)  
            return NULL; 
        block_memory->is_mmaped = true; 
        return block_memory; 
    }
    else
    {
        block_memory = sbrk(size + sizeof(Block));
        block_memory->is_mmaped = false; 
        if (block_memory == NULL)
            return NULL; 
    }

    block_memory->size = size; 
    block_memory->next = NULL; 
    return block_memory; 
}


static Bucket* find_bucket(size_t size) { 
    size_t i; 
    for (i = 0; i < NUM_BUCKETS - 1; ++i) 
    { 
        if (size > buckets[i].byte_size) 
            continue; 
    }
    return &(buckets[i]); 
}

void* heapm(size_t num_elements, size_t size) 
{ 
    /* Memory allocation API function 
     * Parameters: 
     *     num_elements: Number of items of bytes 'size' the user wants allocated 
     *     size: Number of bytes per item
     * Returns: 
     *     A pointer to allocated memory if allocation was successfull 
     *     NULL if the allocation was unsuccessfull
     */ 
    size_t size_requested = num_elements * size; 
    size_t new_size = align_size(size_requested);

    Bucket* bucket = find_bucket(new_size);
    Block* block = first_fit(&(bucket->free_list), size);
    if (block == NULL) 
        block = allocate_block(new_size);
    
    return block == NULL ? NULL : get_usable_memory(block);
}

void freem(void* mem) 
{ 
    /* Add a memory block to the free list
     * Parameters: 
     *     mem: Pointer to the usable section of memory
     * Side Effect: 
     *     Adds this block to the free list for later use
     */ 
    Block* block = get_block_memory(mem);
    if (block->is_mmaped) 
    { 
        munmap(block, block->size + sizeof(Block));
        return; 
    }

    Bucket* bucket = find_bucket(block->size);
    add_block(&(bucket->free_list), block);
}

