
#include "heapm.h"

#define LOOP_SIZE 10000

int main() { 

    for (int i = 0; i < LOOP_SIZE; ++i) { 
        void* _ = heapm(10, 100);
    }

    return 0; 
}
