#include <stdio.h>

void bubbleSortOptimized(int a[], int n)
{
    int i, j, temp;
    int swapped;
    int comparisons = 0;

    for(i = 0; i < n - 1; i++)
    {
        swapped = 0;

        for(j = 0; j < n - i - 1; j++)
        {
            comparisons++;

            if(a[j] > a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                swapped = 1;
            }
        }

        if(swapped == 0)
            break;
    }

    printf("\nOptimized Bubble Sort\n");
    printf("Comparisons = %d\n", comparisons);
}

void bubbleSortNormal(int a[], int n)
{
    int i, j, temp;
    int comparisons = 0;

    for(i = 0; i < n - 1; i++)
    {
        for(j = 0; j < n - i - 1; j++)
        {
            comparisons++;

            if(a[j] > a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }

    printf("\nNormal Bubble Sort\n");
    printf("Comparisons = %d\n", comparisons);
}

int main()
{
    int n, i;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr1[n], arr2[n];

    printf("Enter elements:\n");

    for(i = 0; i < n; i++)
    {
        scanf("%d", &arr1[i]);
        arr2[i] = arr1[i];
    }

    bubbleSortOptimized(arr1, n);
    bubbleSortNormal(arr2, n);

    return 0;
}