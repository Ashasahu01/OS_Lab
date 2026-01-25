#include <stdio.h>
#include <stdlib.h>
int main()
{
    int n; // size of array
    int *arr;

    printf("Enter no of elements: ");
    scanf("%d", &n);

    arr = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
    {
        printf("Enter value for arr[%d] : ", i);
        scanf("%d", arr + i);  //pointer arithmetic &arr[i] = arr+i
    }

    for (int i = 0; i < n; i++)
    {
        printf("arr[%d] = %d \n", i, *(arr + i));
    }

    free(arr);
    return 0;
}