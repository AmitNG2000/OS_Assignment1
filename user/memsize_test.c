#include "kernel/types.h"
#include "user/user.h"

int main() {
    int process_size = memsize();
    printf("Process size: %d bytes\n", process_size);
    int* arr = (int *) (malloc(20 * 1024)); // Allocate 20 KB
    process_size = memsize();
    printf("Process size after malloc: %d bytes\n", process_size);
    free(arr); // Free 20 KB
    process_size = memsize();
    printf("Process size after free: %d bytes\n", process_size);
    return 0;
}