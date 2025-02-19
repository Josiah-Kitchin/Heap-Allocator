
#include "block.h"
#include <criterion.h> 

Test(block, first_fit_found) { 
    // Test that a block of appropiate size is found 
    Block* smaller_block = (Block*)malloc(sizeof(Block) + 10);
    smaller_block->size = 10; 
    smaller_block->next = NULL; 

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
    smaller_block->size = 10; 
    smaller_block->next = larger_block; 

    Block* free_list = larger_block; 
    Block* output_block = first_fit(&free_list, 40);
    cr_assert(!output_block, "Expected block to be null");
}

Test(block, split_block) { 
    Block* larger_block = (Block*)malloc(sizeof(Block) + 20 + sizeof(Block));
    Block* smaller_block = (Block*)malloc(sizeof(Block) + 10 + sizeof(Block));
    larger_block->size = 20 + sizeof(Block); 
    larger_block->next = NULL; 
    smaller_block->size = 10 + sizeof(Block); 
    smaller_block->next = larger_block; 

    Block* free_list = larger_block; 
    Block* output_block = first_fit(&free_list, 15);
    cr_assert(free_list->size == 5, "Expected first_fit to split block, got %lu", free_list->size);
}

