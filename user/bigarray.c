#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/param.h"

#define ARRAY_SIZE (1 << 16) // 2^16
#define NUM_OF_CHILDREN_AND_PARTS 4

// Allocated in global data section which is bigger. 
int array[ARRAY_SIZE];
int pids_arr[NPROC];

int main() {
    
  // Initialize the array with consecutive numbers starting from 0
  for (int i = 0; i < ARRAY_SIZE; i++) {
    array[i] = i;
  }
  // Create child processes.
  int forkn_order = forkn(NUM_OF_CHILDREN_AND_PARTS, pids_arr);
  
  //error
  if (forkn_order < 0) {
      printf("Forkn failed\n");
      exit(1, "Forkn failed\n");
  }


  //parent process
  if (forkn_order == 0) {

      int kiiled_children = 0;
      int exit_statuses[NPROC];
      sleep(1); // allow time for children to start
      if (waitall(&kiiled_children, exit_statuses) < 0) {
        printf("waitall failed\n");
        exit(1, "waitall error");
    }
      // sum the exit statuses of the child processes
      int total_sum = 0;
      for (int i = 0; i < NUM_OF_CHILDREN_AND_PARTS; i++) {
        total_sum+= exit_statuses[i];
      }
      printf("[bigarray parent] Total sum of the array: %d\n", total_sum);
      sleep(1); // allow time for stdout to flush
      exit(total_sum, "[bigarray exit msg] Parent done");
  }
  // Child processes
  if (forkn_order > 0) {
      int child_index = forkn_order - 1;
      int start_index = (child_index) * (ARRAY_SIZE / NUM_OF_CHILDREN_AND_PARTS);
      int end_index = (child_index + 1) * (ARRAY_SIZE / NUM_OF_CHILDREN_AND_PARTS); 

      // Calculate the sum of the assigned part of the array
      int sum = 0;
      for (int i = start_index; i < end_index; i++) {
          sum += array[i];
      }

      // Exit with the calculated sum
      // printf("[bigarray child] Childe forkn order=%d with calculated partly sum=%d\n", forkn_order, sum);
      exit(sum, "Child process exited");
  }
  //never get to this part
  return 0;
}