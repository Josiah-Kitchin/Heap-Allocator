
#include "block.h"
#include <criterion.h> 

Test(block, get_free_block_found) { 
    // Test that a block of appropiate size is found 
    Block largerBlock; 
    largerBlock.size = 20; 
    largerBlock.next = NULL; 
    largerBlock.free = true; 

    Block smallerBlock; 
    smallerBlock.size = 10; 
    smallerBlock.next = &largerBlock; 
    smallerBlock.free = true; 

    Block* free_list = &smallerBlock; 

    Block* outputBlock = get_free_block(&free_list, 15);
    cr_assert(outputBlock, "Expected block to not be null");
    cr_assert(outputBlock->size == 20, "Expected larger block to be chosen");
}

Test(block, get_free_block_not_found) { 
    // Test if null is returned if no block is found 
    Block largerBlock; 
    largerBlock.size = 20; 
    largerBlock.next = NULL; 
    largerBlock.free = true; 

    Block smallerBlock; 
    smallerBlock.size = 10; 
    smallerBlock.next = &largerBlock; 
    smallerBlock.free = true; 

    Block* free_list = &smallerBlock; 

    Block* outputBlock = get_free_block(&free_list, 30);
    cr_assert(!outputBlock, "Expected block to be null");
}
