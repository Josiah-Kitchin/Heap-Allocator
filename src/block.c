

#include "block.h"
/*#include <assert.h> */

static bool is_splittable(Block* block, size_t size_to_split) { 
    return block->size >= sizeof(Block) + size_to_split; 
}

static Block* split_block(Block* block, size_t size_to_split) { 
    /* Create a new block with memory left over from block->size - size_to_split
     * The block->size must be greater than the size requested to split plus the size of a block 
     * to ensure enough space for the new block 
     * Parameters: 
     *     block: Given block to create a new block from 
     *     size_to_split: the new size of the given block, new block will be made of left over bytes
     * Returns: 
     *     A pointer to a new block of size block->size - size_to_split
     * Side Effect: 
     *     Input blocks size is changed to size_to_split
     */
    /*assert(is_splittable(block, size_to_split));*/

    // Move pointer to the extra space 
    Block* new_block = (Block*)((char*)block + size_to_split);
    new_block->size = block->size - sizeof(Block) - size_to_split;
    block->size = size_to_split; 
    return new_block; 
}

void add_block(Block** free_list, Block* block) { 
    /* Add a block to the free list, indicating the block of memory
     * is not in use and may be used later */ 
    block->next = *free_list; 
    *free_list = block; 
}

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
    Block* prev = NULL; 
    Block* current = *free_list; 

    while (current != NULL) { 
        if (current->size >= usable_mem_size) { 
            size_t extra_space = usable_mem_size - current->size; 
            if (is_splittable(current, extra_space)) { 
                Block* left_over = split_block(current, extra_space);
                add_block(free_list, left_over);
            }

            if (prev == NULL) {
                *free_list = current->next; 
            } else { 
                prev->next = current->next; 
            }
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








