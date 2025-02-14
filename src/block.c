

#include "block.h"

Block* get_free_block(Block** free_list, size_t usable_mem_size) { 
    /* Used to reuse blocks that are already allocated and are of appropiate size 
     * Parameters: 
     *     free_list: Linked list of blocks that were freed by the user 
     *     usable_mem_size: Size neccessary for the allocation 
     * Returns: 
     *     Pointer to the block if a block of usable mem size or greater is found 
     *     Null if no free blocks of appropiate size are found
     * Side effects: 
     *     Removes the returned block from the free list (if appropiate block is found)
     */ 
    Block* prev = NULL; 
    Block* current = *free_list; 

    while (current != NULL) { 
        if (current->size >= usable_mem_size) { 
            if (prev == NULL) {
                *free_list = current->next; 
            } else { 
                prev->next = current->next; 
            }
            // Block found 
            current->next = NULL; 
            return current; 
        }
        // Searching next block 
        prev = current; 
        current = current->next; 
    }
    // Block not found 
    return NULL; 
}








