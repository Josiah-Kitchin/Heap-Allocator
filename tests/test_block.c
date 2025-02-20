
#include "block.h"
#include <criterion.h> 

Test(block, first_fit_found) { 
    // Test that a block of appropiate size is found 
    Block* smaller_block = (Block*)malloc(sizeof(Block) + 10);
    smaller_block->size = 10; 
    smaller_block->next = NULL; 
    smaller_block->prev = NULL; 

    Block* free_list = smaller_block; 
    Block* output_block = first_fit(&free_list, 10);
    cr_assert(output_block, "Expected block to not be null");
    cr_assert(output_block->size == 10, "Expected block to be chosen");
}

Test(block, first_fit_not_found) { 
    // Test if null is returned if no block is found 
    Block* larger_block = (Block*)malloc(sizeof(Block) + 20);
    Block* smaller_block = (Block*)malloc(sizeof(Block) + 10);
    larger_block->size = 20; 
    larger_block->next = NULL; 
    larger_block->prev = smaller_block; 

    smaller_block->size = 10; 
    smaller_block->next = larger_block; 
    smaller_block->prev = NULL; 

    Block* free_list = smaller_block; 
    Block* output_block = first_fit(&free_list, 40);
    cr_assert(!output_block, "Expected block to be null");
}

Test(block, split_block) { 
    // Test that blocks are split and put back in the free list when it has excess memory 
    Block* larger_block = (Block*)malloc(sizeof(Block) + 20 + sizeof(Block));
    larger_block->size = 20 + sizeof(Block); 
    larger_block->next = NULL; 
    larger_block->prev = NULL; 

    Block* free_list = larger_block; 
    Block* output_block = first_fit(&free_list, 15);
    cr_assert(free_list->size == 5, "Expected first_fit to split block, got %lu", free_list->size);
}

Test(block, merge_block) { 
    // Test that blocks are merged if contingious 
    Block* left_block = (Block*)malloc(sizeof(Block) + 20 + sizeof(Block) + 20);
    left_block->size = 20; 
    Block* right_block = (Block*)((char*)left_block + sizeof(Block) + 20);
    right_block->size = 20; 

    left_block->next = right_block; 
    left_block->prev = NULL; 
    right_block->next = NULL; 
    right_block->prev = left_block; 

    Block* free_list = left_block; 
    Block* output_block = first_fit(&free_list, 40);
    cr_assert(output_block != NULL, "Expected blocks to be merged");
}

Test(block, multiple_merge_block) { 
    // Test that multiple blocks are merged if contingious 
    Block* first_block = (Block*)malloc((sizeof(Block) + 20) * 3);
    first_block->size = 20; 
    Block* second_block = (Block*)((char*)first_block + sizeof(Block) + 20);
    second_block->size = 20; 
    Block* third_block = (Block*)((char*)second_block + sizeof(Block) + 20);
    third_block->size = 20; 

    first_block->next = second_block; 
    first_block->prev = NULL; 
    second_block->next = third_block; 
    second_block->prev = first_block; 
    third_block->next = NULL; 
    third_block->prev = second_block; 

    Block* free_list = first_block; 
    Block* output_block = first_fit(&free_list, 60);
    cr_assert(output_block != NULL, "Expected multiple blocks to be merged");
}


