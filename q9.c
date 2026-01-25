#include <stdio.h>
int main()
{
    FILE *f1, *f2, *merge;
    char ch;

    f1 = fopen("f1.txt", "r");
    if (f1 == NULL)
    {
        printf("Cannot open f1.txt \n");
        return 1;
    }

    f2 = fopen("f2.txt", "r");
    if (f2 == NULL)
    {
        printf("Cannot open f2.txt \n");
        fclose(f1);
        return 1;
    }

    merge = fopen("merge.txt", "w");
    if (merge == NULL)
    {
        printf("Cannot create merge.txt \n");
        fclose(f1);
        fclose(f2);
        return 1;
    }

    while ((ch = fgetc(f1)) != EOF)
    {
        fputc(ch, merge);
    }

    while ((ch = fgetc(f2)) != EOF)
    {
        fputc(ch, merge);
    }

    printf("Files merged succesfully into merge.txt \n");

    fclose(f1);
    fclose(f2);
    fclose(merge);

    return 0;
}