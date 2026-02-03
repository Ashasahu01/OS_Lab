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

    printf("sum of %d+%d = %d \n ", *ptr1, *ptr2, *ptr1 + *ptr2);

    return 0;
}