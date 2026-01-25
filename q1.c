#include <stdio.h>
int main()
{
    int a;
    int *p;
    char ch;
    char *p1;
    char str[20];
    char *p2;

    printf("Enter any value of a: ");
    scanf("%d", &a);
    printf("Enter any character: ");
    scanf("%c \n", &ch);
    printf("Enter any string value: ");
    scanf("%s \n", str);

    p = &a;
    p1 = &ch;
    p2 = str;

    printf("Address of a using pointer p: %p\n", (void *)p);
    printf("Address of ch using pointer p1: %p\n", (void *)p1);
    printf("Address of s using pointer p2: %p\n", (void *)p2);

    return 0;
}
