
#include "block.h"
#include <stdio.h> 
#include <stdlib.h> 


int main() { 
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
    return 0; 
}
