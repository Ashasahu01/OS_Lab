#include <stdio.h>
#include <unistd.h>

int main()
{
    int choice;

    printf("1. Display directory contents (ls)\n");
    printf("2. Display process tree (pstree)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        execl("/bin/ls", "ls", NULL);
    }
    else if (choice == 2)
    {
        execl("/usr/bin/pstree", "pstree", NULL);
    }
    else
    {
        printf("Invalid choice\n");
    }

    return 0;
}
