
#include "block.h"
#include <stdio.h> 
#include <stdlib.h> 


int main() { 

    Block* larger_block = (Block*)malloc(sizeof(Block) + 20 + 16);
    Block* smaller_block = (Block*)malloc(sizeof(Block) + 10 + 16);
    larger_block->size = 36; 
    larger_block->next = NULL; 
    smaller_block->size = 26; 
    smaller_block->next = larger_block; 

    Block* free_list = larger_block; 
    Block* output_block = first_fit(&free_list, 15);
    printf("The free list has block %lu\n", free_list->size);

    return 0; 
}
