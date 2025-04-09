#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#include <stdio.h>

int main() {
    int process_size = memsize();
    printf("Process size: %d bytes\n", process_size);
    // int* arr = (int *) (malloc(20 * 1024)); // Allocate 20 KB
    // int new_process_size = memsize();
    // printf("Process size after malloc: %d bytes\n", new_process_size);
    // free(arr); // Free 20 KB
    // printf("Process size after free: %d bytes\n", memsize());
    return 0;
}