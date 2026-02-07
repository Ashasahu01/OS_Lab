#include <stdio.h>
#include <unistd.h>

int main()
{
    int pid;

    pid = fork(); // create process

    if (pid < 0)
    {
        printf("Process creation failed\n");
    }
    else if (pid == 0)vi
    {
        // Child process
        printf("This is Child Process\n");
        printf("Child PID  : %d\n", getpid());
        printf("Parent PID : %d\n", getppid());
    }
    else
    {
        // Parent process
        printf("This is Parent Process\n");
        printf("Parent PID : %d\n", getpid());
        printf("Child PID  : %d\n", pid);
    }

    return 0;
}
