#include <stdio.h>
int main()
{
    char s[100];
    char *ptr;
    int i = 0;

    printf("Enter any string: ");
    scanf("%s", s);

    int len = 0;

    ptr = s;
    for (i = 0; *(ptr + i) != '\0'; i++)
    {
        len++;
    }
    printf("Length is %d", len);

    return 0;
}