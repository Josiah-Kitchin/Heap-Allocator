

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

bool is_splittable(Block* block, size_t size_to_split) { 
    /* Returns true if there is enough space for a new block 
     * if block is set to the size "size_to_split" */
    return (block->size >= size_to_split) && (block->size - size_to_split > sizeof(Block)); 
}

Block* split_block(Block* block, size_t size_to_split) { 
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

static void merge_block(Block* first_block, Block* second_block) { 
    /* Merge two blocks together, assuming they are consecutive in memory location 
     * The new size of the block will be the left blocks size + right blocks size + sizeof(Block), 
     * since we can now use the space previously occupied by the block header
     * Parameters: 
     *     first_block: First block in memory to be merged
     *     right_block: Second block in memory to be merged
     * Side effect: 
     *     Changes the size of the first block to fill the size of the second block. 
     *     Any pointer to the second block should no longer be used 
     *    
     */
    first_block->size += sizeof(Block) + second_block->size; 
}

void merge_blocks(Block** free_list) { 
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
            // Current was merged with the next block, 
            // set its next to the block after the block merged 
            current->next = current->next->next; 
            continue; 
        }
        current = current->next; 
    }
}


void remove_block(Block** free_list, Block* block) {
    /* Remove a block from the free list by changing the previous and next pointers 
     * Parameters: 
     *     free_list: linked list of free blocks 
     *     block: Block to remove from the free list 
     * Side Effect: 
     *     Removes block from the free list, it must be called only when it is 
     *     present in the free list 
     * */  

    // Case if block is first block in free list 
    if (block->prev == NULL) {
        *free_list = block->next; 
    } else { 
        block->prev->next = block->next; 
    }

    if (block->next) { 
        block->next->prev = block->prev; 
    }
    block->prev = NULL;
    block->next = NULL;
}

void add_block(Block** free_list, Block* block) { 
    /* Add a block to the free list, indicating the block of memory
     * is not in use and may be used later */ 
    block->next = *free_list; 
    if (block->next != NULL) { 
        block->next->prev = block; 
    }
    block->prev = NULL; 
    *free_list = block; 
}

