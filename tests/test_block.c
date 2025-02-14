
#include "block.h"
#include <criterion.h> 

Test(block, first_fit_found) { 
    // Test that a block of appropiate size is found 
    Block largerBlock; 
    largerBlock.size = 20; 
    largerBlock.next = NULL; 

    Block smallerBlock; 
    smallerBlock.size = 10; 
    smallerBlock.next = &largerBlock; 

    Block* free_list = &smallerBlock; 

    Block* outputBlock = first_fit(&free_list, 10);
    cr_assert(outputBlock, "Expected block to not be null");
    cr_assert(outputBlock->size == 10, "Expected larger block to be chosen");
}

Test(block, first_fit_not_found) { 
    // Test if null is returned if no block is found 
    Block largerBlock; 
    largerBlock.size = 20; 
    largerBlock.next = NULL; 

    Block smallerBlock; 
    smallerBlock.size = 10; 
    smallerBlock.next = &largerBlock; 

    Block* free_list = &smallerBlock; 

    Block* outputBlock = first_fit(&free_list, 30);
    cr_assert(!outputBlock, "Expected block to be null");
}

Test(block, split_block) { 
    // Test if null is returned if no block is found 
    Block largerBlock; 
    largerBlock.size = 20; 
    largerBlock.next = NULL; 

    Block smallerBlock; 
    smallerBlock.size = 10; 
    smallerBlock.next = &largerBlock; 

    Block* free_list = &smallerBlock; 
    Block* outputBlock = first_fit(&free_list, 15 + sizeof(Block));

    cr_assert(free_list->size == 5, "Expected first_fit to split block, got %lu", free_list->size);
}

