// #include "kernel/types.h"
// #include "user/user.h"
// #include "kernel/stat.h"

// #define ARRAY_SIZE (1 << 16) // 2^16
// #define NUM_OF_CHILDREN_AND_PARTS 4


// int main() {
//     int array[ARRAY_SIZE];

//     // Initialize the array with consecutive numbers starting from 0
//     for (int i = 0; i < ARRAY_SIZE; i++) {
//         array[i] = i;
//     }

//     int pids_arr[NUM_OF_CHILDREN_AND_PARTS];
//     int quarter_length = ARRAY_SIZE / NUM_OF_CHILDREN_AND_PARTS;
//     int sum = 0;

//     int forkn_order = forkn(NUM_OF_CHILDREN_AND_PARTS, pids_arr);
//     //error
//     if (forkn_order < 0) {
//         printf("Forkn failed\n");
//         exit(1, "Forkn failed\n");
//     }
//     //parent process
//     if (forkn_order == 0) {

//         int kiiled_children = 0;
//         int exit_statuses[NUM_OF_CHILDREN_AND_PARTS];
//         waitall(&kiiled_children, exit_statuses);
//         // sum the exit statuses of the child processes
//         for (int i = 0; i < NUM_OF_CHILDREN_AND_PARTS; i++) {
//             sum+= exit_statuses[i];
//         }
//         printf("Total sum of the array: %d\n", sum);
//         return sum; //at parent process only
//     }
//     // Child processes
//     if (forkn_order > 0) {
//         int child_index = forkn_order - 1;
//         int start_index = child_index * quarter_length;
//         int end_index = (child_index + 1) * quarter_length; 

//         // Calculate the sum of the assigned part of the array
//         for (int i = start_index; i < end_index; i++) {
//             sum += array[i];
//         }

//         // Exit with the calculated sum
//         printf("Childe forkn order=%d, the partly calculated sum=%d\n", forkn_order, sum);
//         exit(sum, "Child process exited");
//     }
//     //never get to this part
//     return 0;
// }
#include "kernel/types.h"
 #include "kernel/param.h"
 #include "user/user.h"
 
 #define SIZE (1 << 16)
 #define PARTS 4
 
 int arr[SIZE];
 int pids[PARTS];
 
 int main() {
   // Initialize array
   for (int i = 0; i < SIZE; i++)
     arr[i] = i;
 
   int which = forkn(PARTS, pids);
   if (which < 0) {
     fprintf(2, "forkn failed\n");
     exit(1, "");
   }
 
   if (which > 0) {
     // Child process
     int start = (which - 1) * (SIZE / PARTS);
     int end = which * (SIZE / PARTS);
     int sum = 0;
     for (int i = start; i < end; i++)
       sum += arr[i];
 
     printf("Child %d (pid=%d) computed sum = %d\n", which, getpid(), sum);
     exit(sum, "");
   }
 
   // Parent process
   printf("Created children with PIDs: ");
   for (int i = 0; i < PARTS; i++) {
     printf("%d ", pids[i]);
   }
   printf("\n");
 
   int count;
   int statuses[NPROC];
 
   if (waitall(&count, statuses) < 0) {
     fprintf(2, "waitall failed\n");
     exit(1, "");
   }
 
   int total = 0;
   for (int i = 0; i < count; i++)
     total += statuses[i];
 
   printf("Final total = %d\n", total);
   exit(0, "");
 }