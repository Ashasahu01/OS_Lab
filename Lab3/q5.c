#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int pid;

    pid = fork();

    if (pid == 0)
    {
        // Child process
        printf("A) Child PID      : %d\n", getpid());
        printf("B) Parent PID     : %d\n", getppid());
    }
    else
    {
        // Parent process
        printf("C) Parent PID     : %d\n", getpid());

        wait(NULL);   // wait for child to finish

        printf("D) Child PID      : %d\n", pid);
    }

    return 0;
}
