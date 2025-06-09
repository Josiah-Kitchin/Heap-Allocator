
#ifndef BUCKET_H
#define BUCKET_H

#include "block.h"
#define NUM_BUCKETS 3

typedef struct { 
    /* Stores the free list along size the max size of each 
     * block in the bucket. 
     * Used to allocate allocations of blocks in different sized buckets 
     */ 
    Block* free_list; 
    unsigned long byte_size; 
} Bucket; 


#endif
