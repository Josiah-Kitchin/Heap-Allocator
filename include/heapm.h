
#ifndef HEAPM_H
#define HEAPM_H

#include <stdlib.h> 

void* heapm(size_t num_elements, size_t size); 
void freem(void* mem); 

#endif
