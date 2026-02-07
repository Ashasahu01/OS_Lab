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
        printf("Child process started\n");
        printf("Child PID : %d\n", getpid());

        sleep(2); // child finishes early
        printf("Child process exiting\n");
    }
    else
    {
        // Parent process
        printf("Parent process started\n");
        printf("Parent PID : %d\n", getpid());

        sleep(10); // parent sleeps, child becomes zombie

        wait(NULL); // prevents zombie
        printf("Child collected by parent\n");
    }

    return 0;
}
