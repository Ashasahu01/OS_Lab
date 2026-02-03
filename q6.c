#include <stdio.h>
int main()
{
    int n;
    printf("Enter the size of Array: ");
    scanf("%d", &n);

    int arr[n];
    int *ptr = arr;
    int temp;

    printf("Array elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", (ptr + i));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i; j++)
        {
            if (*(ptr + j) > *(ptr + j + 1))
            {
                temp = *(ptr + j);
                *(ptr + j) = *(ptr + j + 1);
                *(ptr + j + 1) = temp;
            }
        }
    }

    printf("Sorted array is : ");
    for (int i = 0; i < n; i++)
    {
        printf("%d \t", *(ptr + i));
    }

    return 0;
}