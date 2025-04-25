#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/param.h"

#define ARRAY_SIZE (1 << 16) // 2^16
#define NUM_OF_CHILDREN_AND_PARTS 4

// Allocated in global data section which is bigger. 
int array[ARRAY_SIZE];
int pids_arr[NUM_OF_CHILDREN_AND_PARTS];

int main() {
    
  // Initialize the array with consecutive numbers starting from 0
  for (int i = 0; i < ARRAY_SIZE; i++) {
    array[i] = i;
  }

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
      printf("Total sum of the array: %d\n", total_sum);
      sleep(1); // allow time for stdout to flush
      exit(total_sum, "Parent done");
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
      printf("Childe forkn order=%d with calculated partly sum=%d\n", forkn_order, sum);
      sleep(1); // allow time for stdout to flush
      exit(sum, "Child process exited");
  }
  //never get to this part
  return 0;
}


// #include "kernel/types.h"
//  #include "kernel/param.h"
//  #include "user/user.h"
 
//  #define SIZE (1 << 16)
//  #define PARTS 4
 
//  int arr[SIZE];
//  int pids[PARTS];
 
//  int main() {
//    // Initialize array
//    for (int i = 0; i < SIZE; i++)
//      arr[i] = i;
 
//    int which = forkn(PARTS, pids);
//    if (which < 0) {
//      fprintf(2, "forkn failed\n");
//      exit(1, "");
//    }
 
//    if (which > 0) {
//      // Child process
//      int start = (which - 1) * (SIZE / PARTS);
//      int end = which * (SIZE / PARTS);
//      int sum = 0;
//      for (int i = start; i < end; i++)
//        sum += arr[i];
 
//      printf("Child %d (pid=%d) computed sum = %d\n", which, getpid(), sum);
//      exit(sum, "");
//    }
 
//    // Parent process
//    printf("Created children with PIDs: ");
//    for (int i = 0; i < PARTS; i++) {
//      printf("%d ", pids[i]);
//    }
//    printf("\n");
 
//    int count;
//    int statuses[NPROC];
 
//    if (waitall(&count, statuses) < 0) {
//      fprintf(2, "waitall failed\n");
//      exit(1, "");
//    }
 
//    int total = 0;
//    for (int i = 0; i < count; i++){
//     total += statuses[i];
//    }
 
//    printf("Final total = %d\n", total);
//    exit(0, "");
//  }