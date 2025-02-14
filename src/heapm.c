

#include "heapm.h"
#include "block.h"
#include <sys/mman.h> 

// Linked list of free blocks 
static Block* free_list = NULL; 

static size_t align_size(size_t size) { 
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
    size = align_size(size);
    Block* block_memory = mmap(NULL, size + sizeof(Block), 
                               PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (block_memory == MAP_FAILED)  
        return NULL; 
    block_memory->size = size; 
    block_memory->next = NULL; 
    return block_memory; 
}

static void* get_usable_memory(Block* block_header) { 
    /* Return the usable memory that comes after the block metadata
     * Parameters: 
     *     block_header: Start of the allocated memory containing block metadata 
     * Returns: 
     *     pointer to useable memory 
     */     
    return (void*)((char*)block_header + sizeof(Block));
}

static Block* get_block_memory(void* memory) { 
    /* Return a pointer to the block header meta data pointer
     * Parameters: 
     *     memory: Start of the usable memory 
     * Returns: 
     *     pointer to block header metadata of usable memory
     */     
    return (Block*)((char*)memory - sizeof(Block));
}

void* heapm(size_t num_elements, size_t size) { 
    /* Memory allocation API function 
     * Parameters: 
     *     num_elements: Number of items of bytes 'size' the user wants allocated 
     *     size: Number of bytes per item
     * Returns: 
     *     A pointer to allocated memory if allocation was successfull 
     *     NULL if the allocation was unsuccessfull
     */ 
    size_t size_requested = num_elements * size; 
    size = align_size(size_requested);

    Block* block = get_free_block(&free_list, size);
    if (block == NULL) 
        block = allocate_block(size_requested);
    
    return block == NULL ? NULL : get_usable_memory(block);
}

void freem(void* mem) { 
    /* Add a memory block to the free list
     * Parameters: 
     *     mem: Pointer to the usable section of memory
     * Side Effect: 
     *     Adds this block to the free list for later use
     */ 
    Block* block = get_block_memory(mem);
    block->next = free_list; 
    free_list = block; 
}

