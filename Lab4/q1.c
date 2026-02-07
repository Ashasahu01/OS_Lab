#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipeA[2], pipeB[2];
    char parentMsg[] = "This is Parent";
    char childMsg[]  = "This is Child";
    char data[100];

    pipe(pipeA);
    pipe(pipeB);

    if (fork() == 0) {   // Child process
        read(pipeA[0], data, sizeof(data));
        printf("Child got: %s\n", data);

        write(pipeB[1], childMsg, strlen(childMsg) + 1);
    } 
    else {              // Parent process
        write(pipeA[1], parentMsg, strlen(parentMsg) + 1);

        read(pipeB[0], data, sizeof(data));
        printf("Parent got: %s\n", data);
    }

    return 0;
}
