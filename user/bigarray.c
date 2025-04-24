#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"

#define ARRAY_SIZE (1 << 16) // 2^16
#define NUM_OF_CHILDREN_AND_PARTS 4


int main() {
    int array[ARRAY_SIZE];

    // Initialize the array with consecutive numbers starting from 0
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i;
    }

    int pids_arr[NUM_OF_CHILDREN_AND_PARTS];
    int quarter_length = ARRAY_SIZE / NUM_OF_CHILDREN_AND_PARTS;
    int sum = 0;

    int forkn_order = forkn(NUM_OF_CHILDREN_AND_PARTS, pids_arr);
    //error
    if (forkn_order < 0) {
        printf("Forkn failed\n");
        exit(1, "Forkn failed\n");
    }
    //parent process
    if (forkn_order == 0) {

        int kiiled_children = 0;
        int exit_statuses[NUM_OF_CHILDREN_AND_PARTS];
        waitall(&kiiled_children, exit_statuses);
        // sum the exit statuses of the child processes
        for (int i = 0; i < NUM_OF_CHILDREN_AND_PARTS; i++) {
            sum+= exit_statuses[i];
        }
        printf("Total sum of the array: %d\n", sum);
        return sum; //at parent process only
    }
    // Child processes
    if (forkn_order > 0) {
        int child_index = forkn_order - 1;
        int start_index = child_index * quarter_length;
        int end_index = (child_index + 1) * quarter_length; 

        // Calculate the sum of the assigned part of the array
        for (int i = start_index; i < end_index; i++) {
            sum += array[i];
        }

        // Exit with the calculated sum
        printf("Childe forkn order=%d, the partly calculated sum=%d\n", forkn_order, sum);
        exit(sum, "Child process exited");
    }
    //never get to this part
    return 0;
}