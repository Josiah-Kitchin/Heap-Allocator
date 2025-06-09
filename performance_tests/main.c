
#include "heapm.h"

#define SIZE 100

int main() 
{ 

    int* arr = heapm(sizeof(int), SIZE);

    for (int i = 0; i < SIZE; i++)
        arr[i] = i; 

    freem(arr);

    return 0; 
}
