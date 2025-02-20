

#include "block.h"

Block* first_fit(Block** free_list, size_t usable_mem_size) { 
    /* Used to reuse blocks that are already allocated and are of appropiate size 
     * The first block to fit will be returned 
     * Parameters: 
     *     free_list: Linked list of blocks that were freed by the user 
     *     usable_mem_size: Size neccessary for the allocation 
     * Returns: 
     *     Pointer to the block if a block of usable mem size or greater is found 
     *     Null if no free blocks of appropiate size are found
     * Side effects: 
     *     Removes the returned block from the free list (if appropiate block is found)
     */ 
    merge_blocks(free_list);

    Block* current = *free_list; 

    while (current != NULL) { 
        if (current->size < usable_mem_size) { 
            // Size is not adequate, keep searching 
            current = current->next; 
            continue; 
        }
        if (is_splittable(current, usable_mem_size)) { 
            Block* left_over = split_block(current, usable_mem_size);
            add_block(free_list, left_over);
        }
        remove_block(free_list, current);
        return current; 
    }

    return NULL; 
}








