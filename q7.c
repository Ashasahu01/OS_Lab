#include <stdio.h>

int main()
{
    FILE *fp;
    char words[50];

    fp = fopen("file.txt", "w");
    if (fp == NULL)
    {
        printf("Invalid!");
        return 1;
    }

    printf("Write something: ");
    gets(words);
    fprintf(fp, "%s", words);
    fclose(fp);

    printf("Information added successfully.\n");

    return 0;
}