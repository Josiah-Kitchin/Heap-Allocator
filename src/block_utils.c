

#include "block.h"

void* get_usable_memory(Block* block_header) { 
    /* Return the usable memory that comes after the block metadata
     * Parameters: 
     *     block_header: Start of the allocated memory containing block metadata 
     * Returns: 
     *     pointer to useable memory 
     */     
    return (void*)((char*)block_header + sizeof(Block));
}

Block* get_block_memory(void* memory) { 
    /* Return a pointer to the block header meta data pointer
     * Parameters: 
     *     memory: Start of the usable memory 
     * Returns: 
     *     pointer to block header metadata of usable memory
     */     
    return (Block*)((char*)memory - sizeof(Block));
}
