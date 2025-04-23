
// #include <unistd.h>
// #include <sys/syscall.h>
// #include <sys/wait.h>
// #include <errno.h>

// #define SYS_forkn 451  // Replace with the actual syscall number for forkn
// #define SYS_waitall 452 // Replace with the actual syscall number for waitall

// int main() {
//     int n = 5; // Number of child processes to create
//     int array[n];

//     // Initialize the array with some values
//     for (int i = 0; i < n; i++) {
//         array[i] = i + 1;
//     }

//     // Call the forkn system call
//     int ret = syscall(SYS_forkn, n);
//     if (ret == -1) {
//         perror("forkn syscall failed");
//         return EXIT_FAILURE;
//     }

//     if (ret == 0) {
//         // Child process
//         printf("Child process (PID: %d) working on array element: %d\n", getpid(), array[getpid() % n]);
//         exit(0); // Child exits after processing
//     } else {
//         // Parent process
//         printf("Parent process (PID: %d) waiting for all children to finish...\n", getpid());

//         // Call the waitall system call
//         ret = syscall(SYS_waitall);
//         if (ret == -1) {
//             perror("waitall syscall failed");
//             return EXIT_FAILURE;
//         }

//         printf("All child processes have finished.\n");
//     }

//     return EXIT_SUCCESS;
// }
