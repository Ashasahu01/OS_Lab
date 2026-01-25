#include <stdio.h>
#include <ctype.h>

char rot_13(char ch)
{
    if (ch >= 'a' && ch <= 'z')
        return 'a' + (ch - 'a' + 13) % 26;
    else if (ch >= 'A' && ch <= 'Z')
        return 'A' + (ch - 'A' + 13) % 26;
    else
        return ch;
}

int main()
{
    FILE *f_in, *f_out;
    int ch;

    f_in = fopen("file.txt", "r");
    f_out = fopen("rot_13.txt", "w");

    if (f_in == NULL || f_out == NULL)
    {
        printf("Cannot open file!\n ");
        return 1;
    }

    while ((ch = fgetc(f_in)) != EOF)
    {
        fputc(rot_13((char)ch), f_out);
    }

    fclose(f_in);
    fclose(f_out);

    printf("rot_13 conversion completed.\n ");
    printf("Check file rot_13.txt for result.\n ");

    return 0;
}
