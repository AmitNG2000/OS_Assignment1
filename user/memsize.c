#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
    return syscall(SYS_memsize);
}