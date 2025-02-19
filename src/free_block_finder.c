

#include "block.h"

static bool is_splittable(Block* block, size_t size_to_split) { 
    /* Returns true if there is enough space for a new block 
     * if block is set to the size "size_to_split" */
    return (block->size >= size_to_split) && (block->size - size_to_split > sizeof(Block)); 
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

    // Move pointer to the extra space 
    Block* new_block = (Block*)((char*)block + sizeof(Block) + size_to_split);
    new_block->size = block->size - sizeof(Block) - size_to_split;
    block->size = size_to_split; 
    return new_block; 
}

static bool is_mergable(Block* first_block, Block* second_block) { 
    /* Check to see if the free block is mergable with the next block in the free list 
     * The block will be mergable if the next block memory address comes right after the end of the 
     * given block
     * Parameters: 
     *    first_block: Block to check if it can merge with the next block 
     *    second_block: Block to check if it can merge with the previous block
     * Returns: 
     *    True if the block can be merged with the next block, false otherwise 
     */ 
    if (first_block == NULL || second_block == NULL)  
        return false; 

    return second_block == (Block*)((char*)first_block+ sizeof(Block) + first_block->size); 
}

static Block* merge_block(Block* first_block, Block* second_block) { 
    /* Merge two blocks together, assuming they are consecutive in memory location 
     * The new size of the block will be the left blocks size + right blocks size + sizeof(Block), 
     * since we can now use the space previously occupied by the block header
     * Parameters: 
     *     first_block: First block in memory to be merged
     *     right_block: Second block in memory to be merged
     * Returns: 
     *     A pointer to the first block, with size increased to cover the second block
     */
    first_block->size = sizeof(Block) + second_block->size; 
    return first_block; 
}

void add_block(Block** free_list, Block* block) { 
    /* Add a block to the free list, indicating the block of memory
     * is not in use and may be used later */ 
    block->next = *free_list; 
    *free_list = block; 
}

static void merge_blocks(Block** free_list) { 
    /* Merge all of the blocks that can be merged in the free list
     * Blocks will be merged if they are consecutive in memory
     * Parameters: 
     *     free_list: linked list of free blocks
     * Side Effect: 
     *     Blocks that can be merged in the free list will be merged
     */ 
    Block* current = *free_list;
    while (current != NULL && current->next != NULL) { 
        if (is_mergable(current, current->next)) { 
            merge_block(current, current->next);
        }
        current = current->next; 
    }
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
            if (prev == NULL) {
                *free_list = current->next; 
            } else { 
                prev->next = current->next; 
            }

            if (is_splittable(current, usable_mem_size)) { 
                Block* left_over = split_block(current, usable_mem_size);
                add_block(free_list, left_over);
            }

            current->next = NULL; 
            return current; 
        }
        // Searching next block 
        prev = current; 
        current = current->next; 
    }

    merge_blocks(free_list);
    // Block not found 
    return NULL; 
}








