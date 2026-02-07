#include <stdio.h>
#include <unistd.h>

int main()
{
    fork();   // first fork
    fork();   // second fork

    printf("Process ID  : %d\n", getpid());
    printf("Parent ID   : %d\n\n", getppid());

    return 0;
}
