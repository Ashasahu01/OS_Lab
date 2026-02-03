#include <stdio.h>
#include <ctype.h>

int main()
{
    FILE *fp;
    char ch;
    int characters = 0, words = 0;
    int Word = 0;

    fp = fopen("file.txt", "r");

    if (fp == NULL)
    {
        printf("Error! File not found.\n");
        return 1;
    }

    while ((ch = fgetc(fp)) != EOF)
    {
        characters++;

        if (isalpha(ch))
        {
            Word = 0;
        }
        else if (Word == 0)
        {
            Word = 1;
            words++;
        }
    }
    fclose(fp);

    printf("Characters: %d\n", characters);
    printf("Words: %d\n", words);

    return 0;
}