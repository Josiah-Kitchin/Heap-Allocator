
#include "heapm.h"
#include <stdio.h> 


int main() { 

    int* array = heapm(sizeof(int), 10);
    for (int i = 0; i < 10; i++) { 
        array[i] = 5; 
    }
    for (int i = 0; i < 10; i++) { 
        printf("%d\n", array[i]);
    }


    return 0; 
}
