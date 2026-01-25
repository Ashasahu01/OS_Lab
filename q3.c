#include <stdio.h>
int main()
{
    int a, b;
    int *ptr1;
    int *ptr2;

    printf("Enter values of a and b: ");
    scanf("%d %d", &a, &b);

    ptr1 = &a;
    ptr2 = &b;

    if (*ptr1 > *ptr2)
        printf("%d is greater", *ptr1);
    else
        printf("%d is greater", *ptr2);

    return 0;
}