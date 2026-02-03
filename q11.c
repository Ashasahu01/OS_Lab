#include <stdio.h>
#include <ctype.h>

int main()
{
    FILE *fp;
    char ch;
    int lowC = 0, upC = 0, other = 0;

    fp = fopen("file.txt", "a");
    if (fp == NULL)
    {
        printf("File could not be opened.\n");
        return 1;
    }

    printf("Enter text (Ctrl+Z then Enter to stop on Windows):\n");

    while ((ch = getchar()) != EOF)
    {
        if (isalpha(ch))
        {
            if (islower(ch))
                lowC++;
            else
                upC++;
        }
        else
        {
            other++;
        }

        if (isalnum(ch))
        {
            fputc(ch, fp);
        }
    }

    fclose(fp);

    printf("\nCharacter Count Summary:\n");
    printf("Lowercase characters : %d\n", lowC);
    printf("Uppercase characters : %d\n", upC);
    printf("Non-alphabetic chars : %d\n", other);

    printf("\nData written to existing file: file.txt\n");

    return 0;
}
